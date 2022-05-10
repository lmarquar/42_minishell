/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_el.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:15 by leon              #+#    #+#             */
/*   Updated: 2022/05/08 11:35:18 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

static int	handle_dup2error()
{
	perror("dup2 failed(system error)\n");
	return (1);
}

static int	com_not_found_exit(void)
{
	printf("Command couldn't be found\n");
	exit(1);
	return (1);
}

int	exec_el(char **arg, char **paths, int fdin, int fdout)
{
	int	i;
	char	*cmd;

	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) < 0)
			return (handle_dup2error());
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) < 0)
			return (handle_dup2error());
		close(fdout);
	}
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], arg[0]);
		execve(cmd, arg, NULL);
		free(cmd);
	}
	free_arr(paths);
	return (com_not_found_exit());
}
