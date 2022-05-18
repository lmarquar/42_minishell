/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:22:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/18 11:11:22 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* @param str pointer to start of the chunk (null-termination not garanted)
* @param expand should content be expanded?
*/
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

/*
* sums the len member in text_chunks up
*/
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

/*
* creates a new string from the the text chunks
*/
char	*join_chunks(t_list *chunks)
{
	char			*buffer;
	size_t			size;
	t_text_chunk	*chunk;
	size_t			offset;

	size = sum_len(chunks) + 1;
	buffer = ft_calloc(size, sizeof (char));
	if (!buffer)
		return (NULL);
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
