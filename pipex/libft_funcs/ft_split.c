/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaderi <mnaderi@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:44:09 by lmarquar          #+#    #+#             */
/*   Updated: 2021/10/26 18:52:57 by mnaderi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**dparray(char *s, char c, int *size)
{
	int		i;
	char	**res;

	i = 0;
	*size = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i])
				(*size)++;
		}
		if (s[i])
			i++;
	}
	res = (char **)malloc(sizeof(char *) * ((*size) + 1));
	if (res)
		*(res + *size) = NULL;
	return (res);
}

static char	*createstring(char *s, int start, int end)
{
	char	*res;
	int		i;

	res = malloc(end + 2 - start);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		res[i] = s[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**delete(char **res, int i)
{
	i--;
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

static char	**finish(char **res, char *s, char c, int sizeofres)
{
	int	sizecounter;
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	sizecounter = 0;
	while (sizecounter < sizeofres)
	{
		if (s[i] == c || !s[i])
		{
			end = i - 1;
			res[sizecounter] = createstring(s, start, end);
			if (!res[sizecounter])
				return (delete(res, sizecounter));
			while (s[i] == c)
				i++;
			start = i;
			sizecounter++;
		}
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	*st;
	char	**res;
	int		size;
	char	car[2];

	car[0] = c;
	car[1] = '\0';
	size = 0;
	if (!s)
		return (NULL);
	st = ft_strtrim(s, car);
	if (!st)
		return (NULL);
	if (!st[0])
	{
		free(st);
		return ((char **)ft_calloc(1, sizeof(char *)));
	}
	res = dparray(st, c, &(size));
	if (!res)
		return (delete(&st, -1));
	res = finish(res, st, c, size);
	free(st);
	return (res);
}
