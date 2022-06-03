/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:12 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/03 13:03:19 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static
int	check_token(char *token)
{
	if (!token)
		return (ft_error(2, "syntax error: no token"));
	if (*token == '\0')
	{
		free(token);
		return (ft_error(2, "syntax error: empty token"));
	}
	if (contains_unquoted_ctrlchr(token))
	{
		free(token);
		return (ft_error(2, "syntax error: unexpected token"));
	}
	return (0);
}

t_redir	*new_redir(char *name, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->name = name;
	redir->type = type;
	return (redir);
}

void	clear_redir(void *redir)
{
	t_redir *r;

	if (!redir)
		return ;
	r = (t_redir *) redir;
	if (r->name)
		free(r->name);
	free(r);
}

int	handle_redirection(t_smp_cmd *cmd, char *token, int type)
{
	t_redir	*redir;

	if (check_token(token) != 0)
		return (2);
	redir = new_redir(token, type);
	ft_lstadd_back(&cmd->redirections, ft_lstnew(redir));
	if (type == HEREDOC)
	{
		cmd->heredoc_count++;
	}
	return (0);
}

int	handle_heredoc(char **heredoc_delimiter, char *token)
{
	if (check_token(token) != 0)
		return (2);
	assign_token(heredoc_delimiter, token);
	return (0);
}
