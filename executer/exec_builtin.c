/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:22 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/31 17:10:41 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exec_builtin(t_bin *bin, char **args, int fdout)
{
	int	only_err_msg;

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
