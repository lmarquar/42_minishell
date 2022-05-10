/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/10 11:07:14 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_init_vars(t_cmd_line **cmd_line, int (*inout)[], int **pid)
{
	if ((*cmd_line)->infile)
		(*inout)[0] = open((*cmd_line)->infile, O_RDONLY);
	else
		(*inout)[0] = STDIN_FILENO;
	if ((*cmd_line)->outfile)
		(*inout)[1] = open((*cmd_line)->outfile, O_RDWR | O_CREAT, 0777);
	else
		(*inout)[1] = STDOUT_FILENO;
	if ((*cmd_line)->heredoc_delimiter)
		(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	if ((*cmd_line)->append > 0)
		(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	*pid = ft_calloc(sizeof(int), (*cmd_line)->pipe_count + 1);
	return (0);
}

char	**create_path_arr(char	*path)
{
	char	**paths;
	int		i;
	char	*cmd;

	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = cmd;
	}
	return (paths);
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

int	execute(t_cmd_line *cmd_line, t_env_var *env_vars)
{
	int		*pid;
	char	**paths;
	int		fd[4];
	size_t	i;
	int		inout[2];

	execute_init_vars(&cmd_line, &inout, &pid);
	paths = create_path_arr(env_vars->val);
	i = 0;
	if (!cmd_line->pipe_count)
	{
		if (cmd_line->simple_commands[i]->is_builtin)
				exec_builtin(cmd_line->simple_commands[i]->args, inout[0], inout[1]);
		else
		{
			pid[i] = fork();
			if (pid[i] == 0)
				exec_el(cmd_line->simple_commands[i]->args, paths, inout[0], inout[1]);
		}
	}
	else
	{
		if (pipe(&(fd[0])) == -1)
			return (3);
		if (cmd_line->heredoc_delimiter)
			heredoc_handler(cmd_line, fd[1]);
		else
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[0]);
				exec_el(cmd_line->simple_commands[i]->args, paths, inout[0], fd[1]);
			}
		}
		if (!cmd_line->heredoc_delimiter)
			i++;
		while ((i < cmd_line->pipe_count && !cmd_line->heredoc_delimiter) || i < (cmd_line->pipe_count - 1))
		{
			if (pipe(&(fd[2])) == -1)
				return (3);
			close(fd[1]);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[2]);
				exec_el(cmd_line->simple_commands[i]->args, paths, fd[0], fd[3]);
			}
			close(fd[0]);
			i++;
			if ((i >= cmd_line->pipe_count && !(cmd_line->heredoc_delimiter)) || i >= (cmd_line->pipe_count - 1))
				break ;
			if (pipe(&(fd[0])) == -1)
				return (3);
			close(fd[3]);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[0]);
				exec_el(cmd_line->simple_commands[i]->args, paths, fd[2], fd[1]);
			}
			close(fd[2]);
			i++;
		}
		if (cmd_line->append > 0)
			i--;
		if ((cmd_line->pipe_count % 2))
		{
			close(fd[1]);
			if (cmd_line->append > 0)
				append(fd[0], inout[1]);
			else
			{
				pid[i] = fork();
				if (pid[i] == 0)
					exec_el(cmd_line->simple_commands[i]->args, paths, fd[0], inout[1]);
			}
			close(fd[0]);
		}
		else
		{
			close(fd[3]);
			if (cmd_line->append > 0)
				append(fd[2], inout[1]);
			else
			{
				pid[i] = fork();
				if (pid[i] == 0)
					exec_el(cmd_line->simple_commands[i]->args, paths, fd[2], inout[1]);
			}
			close(fd[2]);
		}
	}
	size_t	k;
	int error_code;
	k = -1;
	while (*pid)
	{
		waitpid(*pid, &error_code, 0);
		if (error_code != 0 && error_code != 256)
			perror("program failed");
		pid++;
	}
	return (0);
}
