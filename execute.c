/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:48 by chelmerd          #+#    #+#             */
/*   Updated: 2022/04/29 14:00:15 by chelmerd         ###   ########.fr       */
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

int	execute(t_dumpster *dump, t_env_var *env_vars)
{
	int		i;
	int		fd[2];
	char	*cmd;
	int		pid;
	int		exit_code;
	char	**paths;
	char	**arg;

	arg = ft_calloc(3, sizeof(char *));
	arg[0] = dump->in;
	paths = ft_split(env_vars->val, ':');
	if (pipe(fd) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		i = -1;
		while (paths[++i])
		{
			cmd = ft_strjoin(paths[i], "/");
			cmd = ft_strjoin(cmd, arg[0]);
			printf("%s\n", cmd);
			execve(cmd, arg, NULL);
		}
		printf("Command couldn't be found\n");
		free_arr(paths);
		free(cmd);
		exit(1);
	}
	waitpid(pid, &exit_code, 0);
	if (exit_code != 0 && exit_code != 256)
		perror("program failed");
	return (0);
}
