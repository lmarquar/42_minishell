/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 17:43:50 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static
int	exec_in_to_out(t_bin *bin, int *pid)
{
	int			fdin;
	t_cmd_line	*cmd_line;

	cmd_line = bin->cmd_line;
	if (cmd_line->smp_cmds[0]->is_builtin == EXIT)
		bin->exit_code = exec_exit(bin, cmd_line->smp_cmds[0]->args, 0);
	fdin = STDIN_FILENO;
	fdin = get_in_fd(bin, cmd_line->smp_cmds[0]->redirections, fdin);
	if (fdin == -1)
		return (1);
	if (cmd_line->smp_cmds[0]->is_builtin)
		exec_builtin(bin, cmd_line->smp_cmds[0]->args, STDOUT_FILENO);
	else
	{
		*pid = fork();
		if (*pid == 0)
			exec_el(cmd_line->smp_cmds[0]->args, bin, fdin, STDOUT_FILENO);
	}
	return (0);
}

static
void	set_exit_code(t_bin *bin, int exit_code)
{
	if (bin->cmd_line->smp_cmds[0]->is_builtin)
		return ;
	if (WIFSIGNALED(exit_code))
		bin->exit_code = 128 + WTERMSIG(exit_code);
	else if (WIFEXITED(exit_code))
		bin->exit_code = WEXITSTATUS(exit_code);
	else
		perror("program failed");
}

int	wait_for_all_commands(int pid[])
{
	int	last_exit_code;
	int	i;

	last_exit_code = 0;
	i = 0;
	while (pid[i])
	{
		if (waitpid(pid[i], &last_exit_code, 0) == -1)
		{
			perror("waitpid");
			continue ;
		}
		i++;
	}
	return (last_exit_code);
}

static
void	exec_split(t_bin *bin)
{
	if (!bin->cmd_line->pipe_count)
		exec_in_to_out(bin, bin->pid);
	else
		exec_with_pipes(bin, bin->pid);
}

int	execute(t_bin *bin)
{
	int			i;
	int			exit_code;
	t_cmd_line	*cmd_line;

	bin->pid = ft_calloc(bin->cmd_line->cmd_count + 1, sizeof(int));
	cmd_line = bin->cmd_line;
	if (!cmd_line->smp_cmds[0]->cmd)
		return (0);
	exec_split(bin);
	ignore_signals();
	i = 0;
	exit_code = wait_for_all_commands(bin->pid);
	if (exit_code == 2)
		my_rl_go_on_nl();
	set_exit_code(bin, exit_code);
	free(bin->pid);
	return (0);
}
