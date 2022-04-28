/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:22 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:22 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*res;

	i = 0;
	i2 = 0;
	while (s1[i])
		i++;
	while (s2[i2])
		i2++;
	res = malloc(i + i2 + 1);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2])
	{
		res[i + i2] = s2[i2];
		i2++;
	}
	res[i + i2] = '\0';
	return (res);
}
