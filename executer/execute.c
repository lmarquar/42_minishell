/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/06 16:16:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static
int	execute_init_vars(t_cmd_line **cmd_line, int **pid, int *exit)
{
	// if ((*cmd_line)->cmheredoc_count)
	// 	(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	*pid = ft_calloc((*cmd_line)->pipe_count + 2, sizeof(int));
	*exit = 0;
	return (0);
}

static
int	exec_in_to_out(t_bin *bin, int *pid)
{
	if (bin->cmd_line->smp_cmds[0]->is_builtin)
		exec_builtin(bin, bin->cmd_line->smp_cmds[0]->args, STDOUT_FILENO);
	else
	{
		*pid = fork();
		if (*pid == 0)
			exec_el(bin->cmd_line->smp_cmds[0]->args, bin, STDIN_FILENO, STDOUT_FILENO);
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

static
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	get_nmbr_of_outputs(t_smp_cmd **s_cmd_line)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s_cmd_line[i])
	{
		if (((t_redir *)s_cmd_line[i]->redirections))
		{
			printf("redir type:%d\n", ((t_redir *)s_cmd_line[i]->redirections->content)->type);
			res++;
		}
		i++;
	}
	return (res);
}

int	execute(t_bin *bin)
{
	int	i;
	int	fd[4];
	int	exit_code;

	if (!bin->cmd_line->smp_cmds[0]->cmd)
		return (0);
	execute_init_vars(&bin->cmd_line, &(bin->pid), &exit_code);
	if (!bin->cmd_line->pipe_count && bin->cmd_line->smp_cmds[0]->is_builtin == EXIT)
		bin->exit_code = exec_exit(bin, bin->cmd_line->smp_cmds[0]->args, 0);
	if (!bin->cmd_line->pipe_count)
		exec_in_to_out(bin, bin->pid);
	else
		exec_with_pipes(bin, bin->pid, fd);
	ignore_signals();
	i = 0;
	while (bin->pid[i])
	{
		write(1, "pid\n", 4);
		if (waitpid(bin->pid[i], &exit_code, 0) == -1)
		{
			perror("waitpid");
			continue ;
		}
		i++;
	}
	if (exit_code == 2)
		my_rl_go_on_nl();
	set_exit_code(bin, exit_code);
	free(bin->pid);
	return (0);
}
