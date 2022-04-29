/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:51:51 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:03:48 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t n);

/*
* Description
*	Contiguously allocates enough space for count objects that are size bytes of
*	memory each and returns a pointer to the allocated memory.
*	The allocated memory is filled with bytes of value zero.
*
* Return Values
*	If succsesfull, it returns a pointer to allocated memory,
*	otherwise returns NULL.
*/
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	unsigned int	nbr;

	nbr = count * size;
	mem = malloc(nbr);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, nbr);
	return (mem);
}
