/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 17:32:52 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	contains_hdoc_or_in(t_list *redir)
{
	int	type;

	while (redir)
	{
		type = ((t_redir *)redir->content)->type;
		if (type == HEREDOC || type == INPUT)
			return (1);
		redir = redir->next;
	}
	return (0);
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

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
