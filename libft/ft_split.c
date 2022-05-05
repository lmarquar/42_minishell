/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:49:24 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:42:04 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			**ft_split(const char *s, char c);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dst, const void *src, size_t n);

static size_t	calc_arr_len(const char *s, char c);
static char		*next_token(const char *s, char c, size_t *start);

/*
* Description
*	Allocates (with malloc(3)) and returns an array of strings obtained by
*	splitting ’s’ using the character ’c’ as a delimiter. The array is ended
*	by a NULL pointer.
*
* Parameters
*	#1. The string to be split.
*	#2. The delimiter character.
*
* Return Values
*	The array of new strings resulting from the split.
*	NULL if the allocation fails.
*/
char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	len;
	size_t	i;
	size_t	start_index;

	if (!s)
		return (NULL);
	len = calc_arr_len(s, c);
	arr = (char **) malloc(sizeof (char *) * (len + 1));
	i = 0;
	if (arr == NULL)
		return (NULL);
	start_index = 0;
	while (i < len)
	{
		arr[i] = next_token(s, c, &start_index);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static size_t	calc_arr_len(const char *s, char c)
{
	size_t	len;
	int		prev_char_is_delim;

	len = 0;
	prev_char_is_delim = 1;
	while (*s)
	{
		if (*s == c)
		{
			prev_char_is_delim = 1;
		}
		else if (*s != c)
		{
			if (prev_char_is_delim == 1)
				len++;
			prev_char_is_delim = 0;
		}
		s++;
	}
	return (len);
}

static char	*next_token(const char *s, char c, size_t *offset)
{
	char		*token;
	const char	*token_start;
	const char	*s_start;
	size_t		len;

	if (s == NULL)
		return (NULL);
	s_start = s;
	s += *offset;
	while (*s == c)
	{
		s++;
	}
	token_start = s;
	while (*s && *s != c)
		s++;
	len = s - token_start;
	token = (char *) malloc(sizeof (char) * (len + 1));
	if (token == NULL)
		return (NULL);
	token = (char *) ft_memcpy(token, token_start, len);
	token[len] = '\0';
	*offset = s - s_start;
	return (token);
}
