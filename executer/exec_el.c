/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_el.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:15 by leon              #+#    #+#             */
/*   Updated: 2022/06/06 11:47:16 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	com_not_found_exit(void)
{
	printf("Command couldn't be found\n");
	exit(127);
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
	ft_putstr_fd("in exec in current dir\n", open("out.txt", O_CREAT));
	execve(arg[0], arg, bin->env_arr);
	return (com_not_found_exit());
}

static
int	exec_with_paths(char **arg, t_bin *bin)
{
	int		i;
	char	*cmd;

	i = -1;
	ft_putstr_fd("in exec in current dir\n", open("out.txt", O_CREAT));
	while (bin->paths && bin->paths[++i])
	{
		cmd = ft_strjoin(bin->paths[i], arg[0]);
		execve(cmd, arg, bin->env_arr);
		free(cmd);
	}
	return (com_not_found_exit());
}

int	el_get_in_fd(t_list *redirs, int fd)
{
	while (redirs)
	{
		if (((t_redir *)redirs->content)->type == INPUT)
		{
			close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_RDONLY);
		}
		redirs = redirs->next;
	}
	return (fd);
}

int	exec_el(char **arg, t_bin *bin, int fdin, int fdout)
{
	int		i;

	fdin = el_get_in_fd(bin->cmd_line->smp_cmds[0]->redirections, fdin);
	fdout = get_out_fd(bin->cmd_line->smp_cmds[0]->redirections, fdout);
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
		i = exec_in_current_dir(arg, bin);
	else
		i = exec_with_paths(arg, bin);
	exit(i);
	return (0);
}
