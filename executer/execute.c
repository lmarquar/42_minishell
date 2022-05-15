/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/15 15:16:00 by leon             ###   ########.fr       */
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
		waitpid(*pid, &exit_code, 0);
		printf("PID: %d, exit_code: %d\n", *pid, exit_code);
		if (exit_code != 0 && exit_code != 256)
			perror("one of the executed programs failed");
		pid++;
	}
	bin->exit_code = exit_code;
	return (0);
}
