/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/03 13:03:19 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

	delimiter = cmd_line->heredoc_delimiter;
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
