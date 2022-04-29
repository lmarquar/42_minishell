/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:07:30 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:34:36 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t n);

/*
* Description
*	Allocates (with malloc(3)) and returns a substring from the string ´s´.
*
* Parameters
*	#1. The string from which to create the substring.
*	#2. The start index of the substring in the string ’s’.
*	#3. The maximum length of the substring.
*
* Return Values
*	The substring.
*	NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	sub = (char *) malloc(sizeof (char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*sub = '\0';
		return (sub);
	}
	i = 0;
	while (len)
	{
		sub[i] = s[start + i];
		if (sub[i] == '\0')
			break ;
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
