/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:08:52 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 14:36:08 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* tokens can be either words or control operators
*/
static
size_t	next_token_len(const char *s, int quote_state, int unit_is_word)
{
	size_t	token_len;

	token_len = 0;
	quote_state = 0;
	while (s && s[token_len])
	{
		quote_state = quote_state
			+ change_quote_state(quote_state, s[token_len]);
		if (!unit_is_word)
		{
			if (!is_ctrlchr(s[token_len]))
				break ;
		}
		else if (quote_state == NO_QUOTE && is_metachr(s[token_len]))
			break ;
		token_len++;
	}
	return (token_len);
}

char	*next_token(const char *s, int reset)
{
	static size_t	i = 0;
	char			*token;
	size_t			token_len;
	int				quote_state;

	if (reset)
		i = 0;
	quote_state = change_quote_state(NO_QUOTE, s[i]);
	while (quote_state == NO_QUOTE && s[i] && is_space(s[i]))
		i++;
	if (quote_state == NO_QUOTE && is_ctrlchr(s[i]))
		token_len = next_token_len(&s[i], quote_state, 0);
	else
		token_len = next_token_len(&s[i], quote_state, 1);
	if (token_len == 0)
		return (NULL);
	token = ft_calloc(token_len + 1, sizeof (char));
	ft_strlcpy(token, &s[i], token_len + 1);
	i += token_len;
	return (token);
}
