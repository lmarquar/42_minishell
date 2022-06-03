/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:40:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/01 16:58:57 by chelmerd         ###   ########.fr       */
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

int	contains_unquoted_ctrlchr(const char *s)
{
	int	quote_state;

	if (!s)
		return (0);
	quote_state = change_quote_state(-1, *s);
	while (*s)
	{
		quote_state += change_quote_state(quote_state, *s);
		if (quote_state == NO_QUOTE && is_ctrlchr(*s))
			return (1);
		s++;
	}
	return (0);
}
