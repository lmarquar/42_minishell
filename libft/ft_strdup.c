/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:59:14 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 12:48:57 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

/*
* Description
*	Allocates sufficient memory for a copy of the string s1, does the copy,
*	and returns a pointer to it.  The pointer may subsequently be used as an
*	argument to the function free(3).
*
* Return Values
*	A pointer to the duplicate of the string, or
*	NULL if the Allocation fails.
*/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *) malloc(sizeof (char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	dup[len] = '\0';
	while (len)
	{
		dup[len - 1] = s[len - 1];
		len--;
	}
	return (dup);
}
