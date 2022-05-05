/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:36:18 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:33:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Applies the function f to each character of the string passed as argument,
*	and passing its index as first argument. Each character is passed by address
*	to f to be modified if necessary.
*
* Parameters
*	#1. The string on which to iterate.
*	#2. The function to apply to each character.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (*s)
	{
		(f)(i, s);
		s++;
		i++;
	}
}
