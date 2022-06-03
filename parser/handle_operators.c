/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:12 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/01 16:48:57 by chelmerd         ###   ########.fr       */
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

int	handle_redirection(char **member, char *token)
{
	if (check_token(token) != 0)
		return (2);
	assign_token(member, token);
	return (0);
}

int	handle_heredoc(char **heredoc_delimiter, char *token)
{
	if (check_token(token) != 0)
		return (2);
	assign_token(heredoc_delimiter, token);
	return (0);
}
