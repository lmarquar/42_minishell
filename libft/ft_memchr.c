/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:15:21 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:53:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Locates the first occurrence of c (converted to an unsigned char) in string s.
*
* Parameters
*	#1. The string in which to search.
*	#2. The character to locate.
*	#3. The number of bytes to search.
*
* Return Values
*	A pointer to the byte located, or NULL if no such byte exists within n bytes.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*bytes;
	size_t				i;

	bytes = s;
	i = 0;
	while (i < n)
	{
		if (*bytes == (unsigned char)c)
			return ((void *) bytes);
		bytes++;
		i++;
	}
	return (NULL);
}
