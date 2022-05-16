/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/16 14:11:28 by chelmerd         ###   ########.fr       */
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

int	exec_in_to_out(t_bin *bin, int *pid, int fd[])
{
	if (bin->cmd_line->simple_commands[0]->is_builtin)
		exec_builtin(bin, bin->cmd_line->simple_commands[0]->args, fd[4], fd[5]);
	else
	{
		*pid = fork();
		if (*pid == 0)
			exec_el(bin->cmd_line->simple_commands[0]->args, bin, fd[4], fd[5]);
	}
	return (0);
}

void	set_exit_code(t_bin *bin, int exit_code)
{
	if (WIFSIGNALED(exit_code))
		bin->exit_code = 128 + WTERMSIG(exit_code);
	else if (WIFEXITED(exit_code))
	{
		printf("EXIT STATUS:%d\n", WEXITSTATUS(exit_code)); // debug
		bin->exit_code = WEXITSTATUS(exit_code);
	}
	else
		perror("program failed");
}

int	execute(t_bin *bin)
{
	int	*pid;
	int	fd[6];
	int	exit_code;

	execute_init_vars(&bin->cmd_line, &fd, &pid);
	if (!bin->cmd_line->pipe_count)
		exec_in_to_out(bin, pid, fd);
	else
		exec_with_pipes(bin, pid, fd);
	while (*pid)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(*pid, &exit_code, 0);
		printf("PID: %d, exit_code: %d\n", *pid, exit_code);
		set_exit_code(bin, exit_code);
		pid++;
	}
	return (0);
}
