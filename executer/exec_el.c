/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_el.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:15 by leon              #+#    #+#             */
/*   Updated: 2022/06/06 17:36:13 by lmarquar         ###   ########.fr       */
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

int	contains_hdoc_or_in(t_list *redir)
{
	int type;

	while(redir)
	{
		type =	((t_redir *)redir->content)->type;
		if (type == HEREDOC || type == INPUT)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	el_get_in_fd(t_bin *bin, t_list *redirs, int fd)
{
	int	fdtmp;
	char	*name;
	int		type;
	
	fdtmp = fd;
	while (redirs)
	{
		type = ((t_redir *)redirs->content)->type;
		name = ((t_redir *)redirs->content)->name;
		if (type == INPUT)
		{
			if (fdtmp != fd)
				close(fdtmp);
			fdtmp = open(name, O_RDONLY);
		}
		else if (type == HEREDOC)
		{
			if (fdtmp != fd)
				close(fdtmp);
			if (contains_hdoc_or_in(redirs->next))
				dumb_heredoc_handler(bin, name);
			else
				fd = heredoc_handler(bin, name);
			if (bin->exit_code == 2)
				return (-1);
			fdtmp = fd;
		}
		redirs = redirs->next;
	}
	return (fdtmp);
}

int	exec_el(char **arg, t_bin *bin, int fdin, int fdout)
{
	int		i;

	fdin = el_get_in_fd(bin, bin->cmd_line->smp_cmds[0]->redirections, fdin);
	if (fdin == -1)
		exit (2);
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
