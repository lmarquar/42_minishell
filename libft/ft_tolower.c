/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:53:34 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:29:17 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Converts an upper-case letter to the corresponding lower-case letter.
*	The argument must be representable as an unsigned char or the value of EOF.
*
* Return Values
*	If the argument is an upper-case letter, the tolower() function returns the
*	corresponding lower-case letter if there is one; otherwise, the argument is
*	returned unchanged.
*/
int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c - ('A' - 'a'));
	else
		return (c);
}
