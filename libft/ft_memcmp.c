/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:27:06 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:16:11 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Compares byte string s1 against byte string s2.
*	Both strings are assumed to be n bytes long.
*
* Return Values
*	0 if the two strings are identical, otherwise returns the difference between
*	the first two differing bytes (treated as unsigned char values, so that \\200
*	is greater than \\0, for example).  Zero-length strings are always identical.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*bytes1;
	const unsigned char	*bytes2;
	size_t				i;

	bytes1 = s1;
	bytes2 = s2;
	i = 0;
	while (i < n)
	{
		if (*bytes2 - *bytes1 != 0)
			return ((int)*bytes1 - *bytes2);
		bytes1++;
		bytes2++;
		i++;
	}
	return (0);
}
