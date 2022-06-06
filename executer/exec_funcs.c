/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/06 12:57:42 by chelmerd         ###   ########.fr       */
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

int	heredoc_handler(t_cmd_line *cmd_line, int fdout)
{
	char	*in;
	char	*delimiter;
	int		pid;
	int		p_exit;

	(void) cmd_line;
	delimiter = "here-d";
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			in = readline("> ");
			if (!in)
				exit(1);
			if (ft_strcmp(delimiter, in))
			{
				free(in);
				exit(0);
			}
			write(fdout, in, ft_strlen(in));
			write(fdout, "\n", 1);
			free(in);
		}
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	p_exit = 0;
	waitpid(pid, &p_exit, 0);
	if (p_exit == 2)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		return (1);
	}
	return (0);
}
