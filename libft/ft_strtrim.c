/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:28:36 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:25:31 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strtrim(const char *s1, const char *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);

static int	char_in_set(const char c, const char *set);

/*
* Description
*	Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
*	specified in ’set’ removed from the beginning and the end of the string.
*
* Parameters
*	#1. The string to be trimmed.
*	#2. The reference set of characters to trim.
*
* Return Values
*	The trimmed string.
*	NULL if the allocation fails.
*/
char	*ft_strtrim(const char *s1, const char *set)
{
	char		*str;
	const char	*start;
	const char	*end;
	size_t		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (char_in_set(*start, set))
	{
		start++;
	}
	if (start > end)
		return (ft_strdup(""));
	while (char_in_set(*end, set))
	{
		end--;
	}
	len = (end - start) + 1;
	str = (char *) malloc(sizeof (char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, start, len + 1);
	return (str);
}

static int	char_in_set(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
