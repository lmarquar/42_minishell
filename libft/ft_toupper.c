/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:48:09 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:30:31 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Converts an lower-case letter to the corresponding lower-case letter.
*	The argument must be representable as an unsigned char or the value of EOF.
*
* Return Values
*	If the argument is an lower-case letter, the tolower() function returns the
*	corresponding upper-case letter if there is one; otherwise, the argument is
*	returned unchanged.
*/
int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c + ('A' - 'a'));
	else
		return (c);
}
