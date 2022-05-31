/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:40:30 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:26:00 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Copies n bytes from memory area src to memory area dst.
*	If dst and src overlap, behavior is undefined.  Applications in which dst
*	and src might overlap should use memmove(3) instead.
*
* Return Values
*	The original value of dst.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	p = dst;
	s = src;
	while (n > 0)
	{
		*p = *s;
		p++;
		s++;
		n--;
	}
	return (dst);
}
