/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:22:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/19 15:47:51 by lmarquar         ###   ########.fr       */
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

	if (!str || *str == '\0')
		return (NULL);
	chunk = malloc(sizeof (t_text_chunk));
	chunk->str = str;
	chunk->len = 1;
	chunk->expand = expand;
	return (chunk);
}

void	clear_chunk(void *chk_ptr)
{
	t_text_chunk	*chunk;

	if (!chk_ptr)
		return ;
	chunk = (t_text_chunk *) chk_ptr;
	if (chunk->expand == 2 && chunk->str)
		free(chunk->str);
	free(chunk);
}

void	split_into_chunks(t_list **chunks,
							t_text_chunk **chunk,
							int *state,
							char *s)
{
	if (change_quote_state(*state, *s) != 0
		|| (*state != SINGLE_QUOTE && *s == '$'))
	{
		*state = *state + change_quote_state(*state, *s);
		if (*chunk)
		{
			ft_lstadd_back(chunks, ft_lstnew(*chunk));
			*chunk = NULL;
		}
		if (*state != SINGLE_QUOTE && *s == '$')
			*chunk = new_chunk(s, 1);
	}
	else if (*chunk && (*chunk)->str[0] == '$' && *state != SINGLE_QUOTE
		&& (is_quote(*s) || *s == '$' || is_space(*s)
			|| ((*chunk)->len >= 2 && (*chunk)->str[1] == '?')))
	{
		ft_lstadd_back(chunks, ft_lstnew(*chunk));
		*chunk = new_chunk(s, is_dollarchr(*s));
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
