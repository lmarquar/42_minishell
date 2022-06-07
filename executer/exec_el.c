/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_el.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:15 by leon              #+#    #+#             */
/*   Updated: 2022/06/07 14:20:44 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	com_not_found_exit(t_bin *bin)
{
	printf("Command couldn't be found\n");
	clean_exit(bin, 127);
	return (1);
}

static int	is_absolute_or_relative_path(char *path)
{
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

static int	exec_in_current_dir(char **arg, t_bin *bin)
{
	execve(arg[0], arg, bin->env_arr);
	return (com_not_found_exit(bin));
}

static
int	exec_with_paths(char **arg, t_bin *bin)
{
	int		i;
	char	*cmd;

	i = -1;
	while (bin->paths && bin->paths[++i])
	{
		cmd = ft_strjoin(bin->paths[i], arg[0]);
		execve(cmd, arg, bin->env_arr);
		free(cmd);
	}
	return (com_not_found_exit(bin));
}

int	exec_el(char **arg, t_bin *bin, int fdin, int fdout)
{
	int		i;

	fdout = get_out_fd(bin->cmd_line->smp_cmds[0]->redirections, fdout);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) < 0)
			exit (handle_dup2error());
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) < 0)
			exit (handle_dup2error());
		close(fdout);
	}
	if (is_absolute_or_relative_path(arg[0]))
		i = exec_in_current_dir(arg, bin);
	else
		i = exec_with_paths(arg, bin);
	exit(i);
	return (0);
}
