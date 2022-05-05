/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:37:39 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:21:50 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
* Description
*	Locates the first occurrence of the null-terminated string needle in the
*	string haystack, where not more than n characters are searched.
*	Characters that appear after a NUL character are not searched.
*
* Parameters
*	#1. The string haystack to be search in
*	#2. The string needle to be search for
*
* Return Values
*	If needle is an empty string, haystack is returned;
*	if needle occurs nowhere in haystack, NULL is returned;
*	otherwise a pointer to the first character of the first occurrence of needle
*	is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t		needle_len;

	if (*needle == '\0')
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && n >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
		{
			return ((char *) haystack);
		}
		else
		{
			haystack++;
			n--;
		}
	}
	return (NULL);
}
