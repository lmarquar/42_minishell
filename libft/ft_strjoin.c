/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:16:25 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:53:56 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);

/*
* Description
*	Allocates (with malloc(3)) and returns a new string, which is the result of
*	the concatenation of ’s1’ and ’s2’.
*
* Parameters
*	#1. The prefix string.
*	#2. The suffix string.
*
* Return Values
*	The new string.
*	NULL if the allocation fails.
*/
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc(sizeof (char) * (len + 1));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (*s1)
	{
		str[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = '\0';
	return (str);
}
