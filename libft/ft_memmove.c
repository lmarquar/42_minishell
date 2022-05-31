/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:55:57 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:27:40 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Copies n bytes from string src to string dst.
*	The two strings may overlap; the copy is always done in a non-destructive
*	manner.
*
* Return Values
*	The original value of dst.
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	p = dst;
	s = src;
	if (src < dst && dst < src + n)
	{
		p += n;
		s += n;
		while (n--)
		{
			*--p = *--s;
		}
	}
	else
	{
		while (n--)
		{
			*p++ = *s++;
		}
	}
	return (dst);
}
