/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:26:05 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:18:30 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
size_t	ft_strlen(const char *s);

/*
* Description
*	Applies the function ’f’ to each character of the string ’s’, and
*	passing its index as first argument to create a new string (with malloc(3))
*	resulting from successive applications of ’f’.
*
* Parameters
*	#1. The string on which to iterate.
*	#2. The function to apply to each character.
*
* Return Values
*	The string created from the successive applications of ’f’.
*	Returns NULL if the allocation fails.
*/
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	str = (char *) malloc(sizeof (char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		str[i] = (f)(i, *s);
		s++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
