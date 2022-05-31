/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:20:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/23 17:16:59 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
* Description
*	Computes the length of the string s.
*	The strnlen() function attempts to compute the length of s, but never scans
*	beyond the first maxlen bytes of s.
*
* Return Values
*	The number of characters that precede the terminating NUL character. 
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}
