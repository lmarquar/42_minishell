/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:13:28 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:15:04 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Tests for an ASCII character, which is between 0 and 127 dez (0177 octal)
*	inclusive.
*
* Return Values
*	Returns 1 if the character tests true and 0 otherwise.
*/
int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}
