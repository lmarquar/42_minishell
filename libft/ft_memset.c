/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:25:16 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:29:22 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Writes len bytes of value c (converted to an unsigned char) to the string b.
*
* Return Values
*	Its first argument.
*/
void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*p;

	p = b;
	while (n > 0)
	{
		*p = (unsigned char) c;
		p++;
		n--;
	}
	return (b);
}
