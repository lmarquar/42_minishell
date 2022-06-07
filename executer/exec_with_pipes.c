/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:55:02 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 17:42:51 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exec_in_to_pipe(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	int			fdin;
	t_cmd_line	*cmd_line;

	cmd_line = bin->cmd_line;
	fdin = get_in_fd(bin, cmd_line->smp_cmds[0]->redirections, STDIN_FILENO);
	if (fdin == -1)
		return (1);
	if (cmd_line->smp_cmds[0]->is_builtin)
	{
		exec_builtin(bin, cmd_line->smp_cmds[0]->args, fd[1]);
		cmd_line->smp_cmds = cmd_line->smp_cmds + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close(fd[0]);
			exec_el(cmd_line->smp_cmds[0]->args, bin, fdin, fd[1]);
		}
		cmd_line->smp_cmds = cmd_line->smp_cmds + 1;
		(**i)++;
	}
	return (0);
}

int	exec_pipe1_to_pipe2(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	close(fd[1]);
	fd[0] = get_in_fd(bin, bin->cmd_line->smp_cmds[0]->redirections, fd[0]);
	if (fd[0] == -1)
		return (1);
	if (bin->cmd_line->smp_cmds[0]->is_builtin)
	{
		exec_builtin(bin, bin->cmd_line->smp_cmds[0]->args, fd[3]);
		bin->cmd_line->smp_cmds = bin->cmd_line->smp_cmds + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close(fd[2]);
			exec_el(bin->cmd_line->smp_cmds[0]->args, bin, fd[0], fd[3]);
		}
		bin->cmd_line->smp_cmds = bin->cmd_line->smp_cmds + 1;
		(**i)++;
	}
	close(fd[0]);
	return (0);
}

int	exec_pipe2_to_pipe1(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	close(fd[3]);
	fd[2] = get_in_fd(bin, bin->cmd_line->smp_cmds[0]->redirections, fd[0]);
	if (fd[2] == -1)
		return (1);
	if (bin->cmd_line->smp_cmds[0]->is_builtin)
	{
		exec_builtin(bin, bin->cmd_line->smp_cmds[0]->args, fd[1]);
		bin->cmd_line->smp_cmds = bin->cmd_line->smp_cmds + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close(fd[0]);
			exec_el(bin->cmd_line->smp_cmds[0]->args, bin, fd[2], fd[1]);
		}
		bin->cmd_line->smp_cmds = bin->cmd_line->smp_cmds + 1;
		(**i)++;
	}
	close(fd[2]);
	return (0);
}

int	exec_pipe_to_out(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	int			i_fd;
	t_cmd_line	*cmd_line;

	cmd_line = bin->cmd_line;
	i_fd = 0;
	if (!(cmd_line->pipe_count % 2))
		i_fd = 2;
	close(fd[1 + i_fd]);
	fd[i_fd] = get_in_fd(bin, cmd_line->smp_cmds[0]->redirections, i_fd);
	if (fd[i_fd] == -1)
		return (1);
	if (cmd_line->smp_cmds[0]->is_builtin)
		exec_builtin(bin, cmd_line->smp_cmds[0]->args, STDOUT_FILENO);
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
			exec_el(cmd_line->smp_cmds[0]->args, bin, fd[i_fd], STDOUT_FILENO);
	}
	close(fd[i_fd]);
	return (0);
}

int	exec_with_pipes(t_bin *bin, int *pid)
{
	size_t	i[2];
	int		fd[4];

	i[0] = 0;
	i[1] = bin->cmd_line->pipe_count;
	if (pipe(&(fd[0])) == -1)
		return (3);
	if (exec_in_to_pipe(bin, pid, fd, &i))
		return (1);
	while (i[0] < i[1])
	{
		if (pipe(&(fd[2])) == -1)
			return (3);
		exec_pipe1_to_pipe2(bin, pid, fd, &i);
		if (i[0] >= i[1])
			break ;
		if (pipe(&(fd[0])) == -1)
			return (3);
		exec_pipe2_to_pipe1(bin, pid, fd, &i);
	}
	exec_pipe_to_out(bin, pid, fd, &i);
	return (0);
}
