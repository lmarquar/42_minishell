/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:02:52 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:23:28 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Locates the last occurrence of c (converted to a char) in the string pointed
*	to by s.  The terminating null character is considered to be part of the
*	string; therefore if c is \\0, the functions locate the terminating \\0.
*
* Return Values
*	A pointer to the located character,
*	or NULL if the character does not appear in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char) c)
			last = s;
		s++;
	}
	if (*s == (char) c)
		return ((char *) s);
	else
		return ((char *) last);
}
