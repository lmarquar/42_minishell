/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:24:53 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:16:29 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Description
*	Tests for a decimal digit character (aka 0 through 9).
*
* Return Values
*	Returns 1 if the character tests true and 0 otherwise.
*/
int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}
