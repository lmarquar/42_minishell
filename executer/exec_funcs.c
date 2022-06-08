/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/08 16:07:10 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t	decr_int_incr_ptr(size_t *i, void ***ptr)
{
	(*ptr) = (*ptr) + 1;
	*i = *i - 1;
	return (*i);
}

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
