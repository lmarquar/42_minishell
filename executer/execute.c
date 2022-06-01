/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/01 13:54:16 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static
int	execute_init_vars(t_cmd_line **cmd_line, int (*fd)[], int **pid, int *exit)
{
	if ((*cmd_line)->heredoc_delimiter)
		(*cmd_line)->pipe_count = (*cmd_line)->pipe_count + 1;
	*pid = ft_calloc((*cmd_line)->pipe_count + 2, sizeof(int));
	*exit = 0;
	if ((*cmd_line)->infile)
		(*fd)[4] = open((*cmd_line)->infile, O_RDONLY);
	else
		(*fd)[4] = STDIN_FILENO;
	if ((*fd)[4] == -1)
	{
		perror("inputfile not found");
		return (1);
	}
	if ((*cmd_line)->outfile && (*cmd_line)->append > 0)
		(*fd)[5] = open((*cmd_line)->outfile, O_CREAT | O_APPEND | O_RDWR, 0777);
	else if ((*cmd_line)->outfile)
		(*fd)[5] = open((*cmd_line)->outfile, O_CREAT | O_TRUNC | O_RDWR, 0777);
	else
		(*fd)[5] = STDOUT_FILENO;
	if ((*fd)[5] == -1)
	{
		perror("outputfile failed to be created");
		return (1);
	}
	return (0);
}

static
int	exec_in_to_out(t_bin *bin, int *pid, int fd[])
{
	if (bin->cmd_line->smp_cmds[0]->is_builtin)
		exec_builtin(bin, bin->cmd_line->smp_cmds[0]->args, fd[5]);
	else
	{
		*pid = fork();
		if (*pid == 0)
			exec_el(bin->cmd_line->smp_cmds[0]->args, bin, fd[4], fd[5]);
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

int	execute(t_bin *bin)
{
	int	i;
	int	fd[6];
	int	exit_code;

	if (!bin->cmd_line->smp_cmds[0]->cmd)
		return (0);
	i = 0;
	execute_init_vars(&bin->cmd_line, &fd, &(bin->pid), &exit_code);
	if (!bin->cmd_line->pipe_count)
		exec_in_to_out(bin, bin->pid, fd);
	else
		exec_with_pipes(bin, bin->pid, fd);
	ignore_signals();
	while (bin->pid[i])
	{
		if (waitpid(bin->pid[i], &exit_code, 0) == -1)
		{
			perror("waitpid");
			continue ;
		}
		i++;
	}
	set_exit_code(bin, exit_code);
	free(bin->pid);
	return (0);
}
