/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 13:00:20 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/*
* tokens can be either words or control operators
*/
size_t	next_token_len(const char *s, int quote_state, int unit_is_word)
{
	size_t	token_len;

	token_len = 0;
	quote_state = 0;
	while (s && s[token_len])
	{
		quote_state = quote_state + change_quote_state(quote_state, s[token_len]);
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

void	init_cmd_line(t_cmd_line *cmd)
{
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_count = 1;
	cmd->pipe_count = 0;
	cmd->simple_commands = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->append = -1;
}

void	init_smp_cmd(t_smp_cmd **smp_c, char *cmd, char **args, size_t arg_count)
{
	t_smp_cmd	*new;

	new = malloc(sizeof (t_smp_cmd));
	new->cmd = cmd;
	new->args = args;
	new->arg_count = arg_count;
	*smp_c = new;
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = malloc(size);
	ft_bzero(new, size);
	ft_memmove(new, ptr, size);

	return (new);
}

void	add_arg(t_smp_cmd **old, char *arg)
{
	t_smp_cmd	*new;
	char		**new_args;
	size_t		i;

	new_args = ft_calloc((*old)->arg_count + 2, sizeof (char *));
	i = 0;
	while (i < (*old)->arg_count)
	{
		new_args[i] = (*old)->args[i];
		i++;
	}
	new_args[i] = arg;
	init_smp_cmd(&new, (*old)->cmd, new_args, (*old)->arg_count + 1);
	free(*old);
	*old = new;
}

t_text_chunk	*new_chunk(char *str, int expand)
{
	t_text_chunk	*chunk;

	chunk = malloc(sizeof (t_text_chunk));
	chunk->str = str;
	chunk->len = 1;
	chunk->expand = expand;
	return (chunk);
}

void	split_into_chunks(t_list **chunks,
							t_text_chunk **chunk,
							int *state,
							char *s)
{
	if (change_quote_state(*state, *s) != 0 || (*state != 1 && *s == '$'))
	{
		*state = *state + change_quote_state(*state, *s);
		if (*chunk)
		{
			ft_lstadd_back(chunks, ft_lstnew(*chunk));
			*chunk = NULL;
		}
		if (*state != 1 && *s == '$')
			*chunk = new_chunk(s, 1);
	}
	else if (*chunk && (*chunk)->str[0] == '$' && *state != 1
		&& (is_quote(*s) || *s == '$'))
	{
		ft_lstadd_back(chunks, ft_lstnew(*chunk));
		*chunk = NULL;
		if (*s == '$')
			*chunk = new_chunk(s, 1);
	}
	else if (*chunk == NULL)
		*chunk = new_chunk(s, 0);
	else
		(*chunk)->len++;
}

void	print_text_chunks(t_list *chunks)
{
	size_t			size;
	char			*buffer;
	t_text_chunk	*chunk;
	size_t			i;

	i = 0;
	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		size = chunk->len + 1;
		buffer = ft_calloc(size, sizeof (char));
		ft_strlcpy(buffer, chunk->str, size);
		printf("text_chunk[%zu]:%s, len:%zu, expand:%d|\n", i, buffer, chunk->len, chunk->expand);
		chunks = chunks->next;
		i++;
	}
}

void	expansion(t_list *chunks, t_env_var *env)
{
	t_text_chunk	*chunk;

	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		if (chunk->expand)
		{
			if (chunk->len == 1)
				chunk->expand = 0;
			else
				expand_env_var(chunk, env);
		}
		chunks = chunks->next;
	}
}

size_t	sum_len(t_list *chunks)
{
	size_t			total_len;
	t_text_chunk	*chunk;

	total_len = 0;
	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		total_len += chunk->len;
		chunks = chunks->next;
	}
	return (total_len);
}

char	*join_chunks(t_list *chunks)
{
	char			*buffer;
	size_t			size;
	t_text_chunk	*chunk;
	t_list			*start;
	size_t			offset;

	start = chunks;
	size = sum_len(chunks) + 1;
	buffer = ft_calloc(size, sizeof (char));
	offset = 0;
	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		ft_memcpy(buffer + offset, chunk->str, chunk->len);
		offset += chunk->len;
		chunks = chunks->next;
	}
	return (buffer);
}

void	interpret_quotes(char **str, t_env_var *env)
{
	char			*result;
	int				quote_state;
	size_t			i;
	t_list			*text_chunks;
	t_text_chunk	*text_chunk;

	text_chunk = NULL;
	text_chunks = NULL;
	i = 0;
	quote_state = -1;
	while ((*str)[i])
	{
		split_into_chunks(&text_chunks, &text_chunk, &quote_state, &(*str)[i]);
		i++;
	}
	if (text_chunk)
		ft_lstadd_back(&text_chunks, ft_lstnew(text_chunk));
	(void) env;
	print_text_chunks(text_chunks);
	expansion(text_chunks, env);
	result = join_chunks(text_chunks);
	//free(*str);
	//clear text_chunks
	*str = result;
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env)
{
	int			error;
	char		*token;
	t_smp_cmd	*smp_cmd;

	error = 0;
	token = next_token(input, 1);
	init_smp_cmd(&smp_cmd, NULL, ft_calloc(2, sizeof (char *)), 0);
	init_cmd_line(cmd_line);
	cmd_line->simple_commands = ft_calloc(3, sizeof (t_smp_cmd));
	while (token)
	{
		printf("token:%s\n", token);
		if (is_ctrlchr(token[0]))
		{
			if (ft_strncmp("<", token, 2) == 0)
				cmd_line->infile = next_token(input, 0);
			else if (ft_strncmp("<<", token, 3) == 0)
				cmd_line->heredoc_delimiter = next_token(input, 0);
			else if (token[0] == '>')
			{
				cmd_line->outfile = next_token(input, 0);
				if (token[1] == '>')
					cmd_line->append = 1;
			}
			else if (ft_strncmp("|", token, 2) == 0)
			{
				cmd_line->simple_commands[cmd_line->cmd_count - 1] = smp_cmd;
				init_smp_cmd(&smp_cmd, NULL, ft_calloc(1, sizeof (char *)), 0);
				cmd_line->pipe_count++;
				cmd_line->cmd_count++;
			}
			else
			{
				printf("Control charater ('%s') not regonized.\n", token);
				error = 1;
				free(token);
			}
		}
		else
		{
			interpret_quotes(&token, env);
			// expand_env_vars(&token, env);
			if (!smp_cmd->cmd)
				smp_cmd->cmd = token;
			add_arg(&smp_cmd, token);
		}
		token = next_token(input, 0);
	}
	cmd_line->simple_commands[cmd_line->cmd_count - 1] = smp_cmd;
	show_cmd_line(cmd_line);
	return (error);
}
