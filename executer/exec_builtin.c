/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:22 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/04 23:03:41 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_get_out_fd(t_list *redirs, int pipe_fd)
{
	int	fd;

	fd = pipe_fd;
	while (redirs)
	{
		if (((t_redir *)redirs->content)->type == OUTPUT)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		else if (((t_redir *)redirs->content)->type == APPEND)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		redirs = redirs->next;
	}
	return (fd);
}

int	exec_builtin(t_bin *bin, char **args, int fdout)
{
	int	only_err_msg;

	fdout = builtin_get_out_fd(bin->cmd_line->smp_cmds[0]->redirections, fdout);
	only_err_msg = 0;
	if (bin->cmd_line->pipe_count)
		only_err_msg = 1;
	if (bin->cmd_line->smp_cmds[0]->is_builtin == ECHO)
		bin->exit_code = exec_echo(fdout, args);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == ENV)
		bin->exit_code = exec_env(fdout, bin->env, args);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == PWD)
		bin->exit_code = exec_pwd(bin->cwd, fdout);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == EXPORT)
		bin->exit_code = exec_export(fdout, bin, &(args[1]), only_err_msg);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == CD)
		bin->exit_code = exec_cd(args[1], &bin->cwd, bin->env, only_err_msg);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == UNSET)
		bin->exit_code = exec_unset(&args[1], bin);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == EXIT)
		bin->exit_code = exec_exit(bin, args, only_err_msg);
	return (0);
}
