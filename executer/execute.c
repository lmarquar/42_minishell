/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/10 12:38:02 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_init_vars(t_cmd_line **cmd_line, int (*fd)[], int **pid)
{
	if ((*cmd_line)->infile)
		(*fd)[4] = open((*cmd_line)->infile, O_RDONLY);
	else
		(*fd)[4] = STDIN_FILENO;
	if ((*cmd_line)->outfile)
		(*fd)[5] = open((*cmd_line)->outfile, O_RDWR | O_CREAT, 0777);
	else
		(*fd)[5] = STDOUT_FILENO;
	if ((*cmd_line)->heredoc_delimiter)
		(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	if ((*cmd_line)->append > 0)
		(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	*pid = ft_calloc((*cmd_line)->pipe_count + 2, sizeof(int));
	return (0);
}

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (1);
	return (0);
}

int	exec_builtin(char **args, int fdin, int fdout)
{
	if (ft_strcmp(args[0], "cd"))
		exec_cd(args[1]);

	//currently unused:
	fdin++;
	fdout++;
	return (0);
}

int exec_in_to_out(t_bin *bin, int *pid, int fd[])
{
	if (bin->cmd_line->simple_commands[0]->is_builtin)
			exec_builtin(bin->cmd_line->simple_commands[0]->args, fd[4], fd[5]);
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
			exec_el(bin->cmd_line->simple_commands[0]->args, bin->paths, fd[4], fd[5]);
	}
	return (0);
}

int	exec_in_to_pipe(t_bin *bin, int *pid, int fd[], size_t *i)
{
		if (pipe(&(fd[0])) == -1)
			return (3);
		if (bin->cmd_line->heredoc_delimiter)
			heredoc_handler(bin->cmd_line, fd[1]);
		else
		{
			pid[*i] = fork();
			if (pid[*i] == 0)
			{
				close(fd[0]);
				exec_el(bin->cmd_line->simple_commands[*i]->args, bin->paths, fd[4], fd[1]);
			}
		}
		(*i)++;
		return (0);
}

int	exec_pipe1_to_pipe2(t_bin *bin, int *pid, int fd[], size_t *i)
{
	if (pipe(&(fd[2])) == -1)
		return (3);
	pid[*i] = fork();
	if (pid[*i] == 0)
	{
		close(fd[2]);
		exec_el(bin->cmd_line->simple_commands[*i]->args, bin->paths, fd[0], fd[3]);
	}
	close(fd[0]);
	close(fd[3]);
	(*i)++;
	return (0);
}

int	exec_pipe2_to_pipe1(t_bin *bin, int *pid, int fd[], size_t *i)
{
	if (pipe(&(fd[0])) == -1)
		return (3);
	pid[*i] = fork();
	if (pid[*i] == 0)
	{
		close(fd[0]);
		exec_el(bin->cmd_line->simple_commands[*i]->args, bin->paths, fd[2], fd[1]);
	}
	close(fd[2]);
	close(fd[1]);
	(*i)++;
	return (0);
}

int	exec_pipe1_to_out(t_bin *bin, int *pid, int fd[], size_t *i)
{
	if (bin->cmd_line->append > 0)
		append(fd[0], fd[5]);
	else
	{
		pid[*i] = fork();
		if (pid[*i] == 0)
			exec_el(bin->cmd_line->simple_commands[*i]->args, bin->paths, fd[0], fd[5]);
	}
	close(fd[0]);
	return (0);
}

int	exec_pipe2_to_out(t_bin *bin, int *pid, int fd[], size_t *i)
{
	if (bin->cmd_line->append > 0)
		append(fd[2], fd[5]);
	else
	{
		pid[*i] = fork();
		if (pid[*i] == 0)
			exec_el(bin->cmd_line->simple_commands[*i]->args, bin->paths, fd[2], fd[5]);
	}
	close(fd[2]);
	return (0);
}

int	exec_with_pipes(t_bin *bin, int *pid, int fd[])
{
	size_t	i;

	i = 0;
	exec_in_to_pipe(bin, pid, fd, &i);
	if (bin->cmd_line->heredoc_delimiter)
		i--;
	while ((i < bin->cmd_line->pipe_count && !bin->cmd_line->heredoc_delimiter) || i < (bin->cmd_line->pipe_count - 1))
	{
		exec_pipe1_to_pipe2(bin, pid, fd, &i);
		if ((i >= bin->cmd_line->pipe_count && !(bin->cmd_line->heredoc_delimiter)) || i >= (bin->cmd_line->pipe_count - 1))
			break ;
		exec_pipe2_to_pipe1(bin, pid, fd, &i);
	}
	if (bin->cmd_line->append > 0)
		i--;
	if ((bin->cmd_line->pipe_count % 2))
		exec_pipe1_to_out(bin, pid, fd, &i);
	else
		exec_pipe2_to_out(bin, pid, fd, &i);
	return (0);
}

int	execute(t_bin *bin)
{
	int		*pid;
	int		fd[6];
	int		error_code;
	int		k;

	execute_init_vars(&bin->cmd_line, &fd, &pid);
	if (!bin->cmd_line->pipe_count)
		exec_in_to_out(bin, pid, fd);
	else
		exec_with_pipes(bin, pid, fd);
	k = -1;
	while (pid[++k])
	{
		waitpid(pid[k], &error_code, 0);
		if (error_code != 0 && error_code != 256)
			perror("program failed");
		else
			printf("PID: %d, EXIT_CODE: %d\n", pid[k], error_code);
	}
	free(pid);
	return (0);
}
