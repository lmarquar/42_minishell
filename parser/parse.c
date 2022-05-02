/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/02 17:09:55 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



/*
* the quote state will be hold until a matching quote is encountered.
*/
int	change_quote_state(int state, char c)
{
	if (!(c == '\'' || c == '"'))
		return (state);
	if (state == NO_QUOTE && c == '\'')
		return (SINGLE_QUOTE);
	if (state == NO_QUOTE && c == '"')
		return (DOUBLE_QUOTE);
	if (state == SINGLE_QUOTE && c == '\'')
		return (NO_QUOTE);
	if (state == DOUBLE_QUOTE && c == '"')
		return (NO_QUOTE);
	return (state);
}

size_t	next_token_len(const char *s, int quote_state, int unit_is_word)
{
	size_t	token_len;

	token_len = 0;
	quote_state = 0;
	while (s && s[token_len])
	{
		quote_state = change_quote_state(quote_state, s[token_len]);
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

int	parse(const char *input, t_cmd_line *cmd_line)
{
	int	error;
	char *token;
	t_smp_cmd	smp_cmd;

	error = 0;
	token = next_token(input, 1);
	while (token)
	{
		printf("token:%s\n", token);
		if (is_ctrlchr(token[0]))
		{
			if (token[0] == '<' && token[1] == '\0')
				cmd_line->infile = next_token(input, 0);
			else if (token[0] == '<' && token[1] == '<')
				cmd_line->heredoc_delimiter = next_token(input, 0);
			else if (token[0] == '>')
			{
				cmd_line->outfile = next_token(input, 0);
				if (token[1] == '>')
					cmd_line->append = 1;
			}
			else if (token[0] == '|' && token[1] == '\0')
			{
				cmd_line->pipe_count++;
			}
			else
				printf("Control charater ('%s') not regonized.\n", token);
		}

		token = next_token(input, 0);
	}
	cmd_line->simple_commands = ft_calloc(cmd_line->cmd_count + 1, sizeof (t_smp_cmd));

	return (error);
}