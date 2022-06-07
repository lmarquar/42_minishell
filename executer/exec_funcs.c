/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 14:58:04 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	while (contains_hdoc_or_in(redirs))
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
				fdtmp = heredoc_handler(bin, name);
			if (bin->exit_code == 2)
				return (-1);
		}
		redirs = redirs->next;
	}
	if (fdtmp == -1 && type == INPUT)
		custom_error(-1, name, "No such file or directory");
	else if (fdtmp == -1 && type == HEREDOC)
		custom_error(-1, name, "heredoc execution failed");
	return (fdtmp);
}

int	get_out_fd(t_list *redirs, int pipe_fd)
{
	int	fd;

	fd = pipe_fd;
	while (redirs)
	{
		if (((t_redir *)redirs->content)->type == OUTPUT)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		else if (((t_redir *)redirs->content)->type == APPEND)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		redirs = redirs->next;
	}
	return (fd);
}

void	close_ifn_inout(int fd)
{
	if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
		close(fd);
}

int	handle_dup2error(void)
{
	perror("dup2 failed(system error)\n");
	return (1);
}

int	append(int fdin, int fdout)
{
	char	c;
	int		i;

	while (read(fdout, &c, 1) > 0)
		;
	i = read(fdin, &c, 1);
	while (i > 0)
	{
		write(fdout, &c, 1);
		i = read(fdin, &c, 1);
	}
	return (0);
}

int	heredoc_handler(t_bin *bin, char *delim)
{
	char	*in;
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			in = readline("> ");
			if (!in)
				exit(1);
			if (ft_strcmp(delim, in))
			{
				free(in);
				exit(0);
			}
			write(fd[1], in, ft_strlen(in));
			write(fd[1], "\n", 1);
			free(in);
		}
		exit(1);
	}
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &bin->exit_code, 0);
	return (fd[0]);
}

int	dumb_heredoc_handler(t_bin *bin, char *delim)
{
	char	*in;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			in = readline("> ");
			if (!in)
				exit(1);
			if (ft_strcmp(delim, in))
			{
				free(in);
				exit(0);
			}
			free(in);
		}
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &bin->exit_code, 0);
	return (0);
}
