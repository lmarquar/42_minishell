/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:16:57 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:18:41 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Tests for any printing character. ASCII: (32 - 126 dez) (040 - 126 octal)
*
* Return Values
*	Returns 1 if the character tests true and 0 otherwise.
*/
int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (1);
	else
		return (0);
}
