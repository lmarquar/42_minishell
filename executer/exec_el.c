/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_el.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:15 by leon              #+#    #+#             */
/*   Updated: 2022/05/18 14:51:28 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	com_not_found_exit(void)
{
	printf("Command couldn't be found\n");
	exit(127);
	return (1);
}

int	is_absolute_or_relative_path(char *path)
{
	if (ft_strncmp(path, "/", 1) == 0
		|| ft_strncmp(path, "./", 2) == 0
		|| ft_strncmp(path, "../", 3) == 0)
		return (1);
	return (0);
}

int exec_in_current_dir(char **arg, t_bin *bin, int fdin, int fdout)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	if (is_absolute_or_relative_path(arg[0]))
	{
		execve(arg[0], arg, bin->env_arr);
		return (com_not_found_exit());
	}
	return (1);
}

int exec_with_paths(char **arg, t_bin *bin, int fdin, int fdout)
{
	int		i;
	char	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	while (bin->paths[++i])
	{
		cmd = ft_strjoin(bin->paths[i], arg[0]);
		execve(cmd, arg, bin->env_arr);
		free(cmd);
	}
	return (com_not_found_exit());
}

int	exec_el(char **arg, t_bin *bin, int fdin, int fdout)
{
	int		i;

	if (is_absolute_or_relative_path(arg[0]))
		i = exec_in_current_dir(arg, bin, fdin, fdout);
	else
		i = exec_with_paths(arg, bin, fdin, fdout);
	return (i);
}
