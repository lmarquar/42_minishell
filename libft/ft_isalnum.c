/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:09:59 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:11:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Tests for any character for which isalpha or isdigit is true.
*
* Return Values
*	Returns 1 if the character tests true and 0 otherwise.
*/
int	ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}
