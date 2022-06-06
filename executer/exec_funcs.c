/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/06 17:37:24 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
