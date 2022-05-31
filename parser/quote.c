/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:40:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/16 11:45:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* the quote state will be hold until a matching quote is encountered.
*/
int	change_quote_state(int state, char c)
{
	if (!(c == '\'' || c == '"'))
		return (0);
	if (state == -1)
		return (is_quote(c) + 1);
	if (state == NO_QUOTE && c == '\'')
		return (SINGLE_QUOTE);
	if (state == NO_QUOTE && c == '"')
		return (DOUBLE_QUOTE);
	if (state == SINGLE_QUOTE && c == '\'')
		return (-SINGLE_QUOTE);
	if (state == DOUBLE_QUOTE && c == '"')
		return (-DOUBLE_QUOTE);
	return (0);
}

int	has_unclosed_quotes(const char *s)
{
	int	q_state;
	int	change;

	q_state = NO_QUOTE;
	while (s && *s)
	{
		change = change_quote_state(q_state, *(s++));
		if (!change)
			continue ;
		q_state += change;
	}
	if (q_state != NO_QUOTE)
		return (1);
	return (0);
}
