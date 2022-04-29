/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:04:57 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:15:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Lexicographically compare the null-terminated strings s1 and s2.
*	Compares not more than n characters. characters that appear after a NUL
*	character are not compared.
*
* Return Values
*	An integer greater than, equal to, or less than 0, according as the string
*	s1 is greater than, equal to, or less than the string s2. The comparison is
*	done using unsigned characters, so that \\200 is greater than \\0.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (*s1 == '\0' && *s2)
			return (-(unsigned char)*s2);
		if (*s1 && *s2 == '\0')
			return ((unsigned char)*s1);
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
