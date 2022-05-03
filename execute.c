/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/03 15:16:53 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

int	exec_el(char **arg, char **paths, int fdin, int fdout)
{
	int	i;
	char	*cmd;

	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdin);
	}
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, arg[0]);
		execve(cmd, arg, NULL);
		free(cmd);
	}
	printf("Command couldn't be found\n");
	free_arr(paths);
	exit(1);

	return (0);
}

int	execute(t_cmd_line *cmd_line, t_env_var *env_vars)
{
	int		p_count;
	int		*pid;
	int		exit_code;
	char	**paths;
	char	**arg;
	int		fd[4];
	int		i;
	int		k;

	arg = cmd_line->simple_commands[0]->args;
	p_count = cmd_line->pipe_count;
	paths = ft_split(env_vars->val, ':');
	pid = ft_calloc(sizeof(int), p_count + 1);
	i = 0;
	if (!p_count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			exec_el(arg, paths, STDIN_FILENO, STDOUT_FILENO);
	}
	else
	{
		if (pipe(&(fd[0])) == -1)
			return (3);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close(fd[1]);
			exec_el(arg, paths, STDIN_FILENO, fd[0]);
		}
		while (++i < (p_count - 2))
		{
			arg = cmd_line->simple_commands[i]->args;
			if (pipe(&(fd[2])) == -1)
				return (3);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[0]);
				close(fd[3]);
				exec_el(arg, paths, fd[1], fd[2]);
			}
			close(fd[0]);
			close(fd[1]);
			i++;
			arg = cmd_line->simple_commands[i]->args;
			if (pipe(fd) == -1)
				return (3);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[1]);
				close(fd[2]);
				exec_el(arg, paths, fd[3], fd[0]);
			}
			close(fd[2]);
			close(fd[3]);
			i++;
		}
		arg = cmd_line->simple_commands[i]->args;
		if (!(p_count % 2))
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[0]);
				exec_el(arg, paths, fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[2]);
				exec_el(arg, paths, fd[3], STDOUT_FILENO);
			}
			close(fd[2]);
			close(fd[3]);
		}
	}
	k = -1;
	while (++k <= i)
	{
		waitpid(pid[k], &exit_code, 0);
		if (exit_code != 0 && exit_code != 256)
			perror("program failed");
	}
	return (0);
}
