/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/04 16:14:07 by chelmerd         ###   ########.fr       */
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
		i = dup2(fdin, STDIN_FILENO);
		if (i < 0)
			perror("dup2error(in)\n");
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		i = dup2(fdout, STDOUT_FILENO);
		if (i < 0)
			perror("dup2error(out)\n");
		close(fdout);
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

int	heredoc_handler(char *delimiter, int fdout)
{
	char	*in;
	int		i;

	in = "";
	i = ft_strlen(delimiter);
	while(ft_strncmp(delimiter, in, i))
	{
		in = readline(">");
		write(fdout, in, ft_strlen(in));
	}
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
	int		in;
	int		out;

	if (cmd_line->infile)
		in = open(cmd_line->infile, O_RDONLY);
	else
		in = STDIN_FILENO;
	if (cmd_line->outfile)
		out = open(cmd_line->outfile, O_WRONLY | O_CREAT, 0666);
	else
		out = STDOUT_FILENO;
	arg = cmd_line->simple_commands[0]->args;
	i = -1;
	p_count = cmd_line->pipe_count;
	paths = ft_split(env_vars->val, ':');
	pid = ft_calloc(sizeof(int), p_count + 1);
	i = 0;
	if (!p_count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			exec_el(arg, paths, in, out);
		if (cmd_line->heredoc_delimiter)
			heredoc_handler(cmd_line->heredoc_delimiter, out);
	}
	else
	{
		if (pipe(&(fd[0])) == -1)
			return (3);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close(fd[0]);
			exec_el(arg, paths, in, fd[1]);
		}
		while (++i < p_count)
		{
			arg = cmd_line->simple_commands[i]->args;
			if (pipe(&(fd[(i % 2) * 2])) == -1)
				return (3);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[i % 2]);
				close(fd[2 + ((i + 1) % 2)]);
				exec_el(arg, paths, fd[((i + 1) % 2) * 2], fd[1 + (i % 2) * 2]);
			}
			close(fd[((i + 1) % 2) * 2]);
			close(fd[1 + ((i + 1) % 2) * 2]);
		}
		arg = cmd_line->simple_commands[i]->args;
		if ((p_count % 2))
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[1]);
				exec_el(arg, paths, fd[0], out);
			}
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[3]);
				exec_el(arg, paths, fd[2], out);
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
