/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:22:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/09 15:34:06 by chelmerd         ###   ########.fr       */
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
	t_list			*start;
	size_t			offset;

	start = chunks;
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

/*
* chunks with the expand flag had their strings allocated seperatly
*/
void	clear_chunk(void *chk_ptr)
{
	t_text_chunk	*chunk;

	chunk = (t_text_chunk *) chk_ptr;
	free(chunk);
}
