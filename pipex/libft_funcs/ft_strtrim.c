/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:32:04 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:32:04 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	compare(char const *s, char const *set, int i)
{
	int	k;
	int	res;

	k = 0;
	res = 0;
	while (set[k])
	{
		if (set[k] == s[i])
			res = 1;
		k++;
	}
	return (res);
}

static int	findstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (compare(s1, set, i) != 0)
		i++;
	return (i);
}

static int	findend(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	i = i - 1;
	while (compare(s1, set, i))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	int		i2;
	char	*res;

	if (!s1 || !set)
		return ((char *)s1);
	start = findstart (s1, set);
	if (!s1[start])
		return (ft_calloc(1, 1));
	end = findend (s1, set);
	res = ft_calloc (end + 2 - start, 1);
	if (!res)
		return (NULL);
	i2 = start;
	i = 0;
	while (i2 <= end)
	{
		res[i] = s1[i2];
		i++;
		i2++;
	}
	return (res);
}
