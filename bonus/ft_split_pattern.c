#include "bonus.h"

static int	chrn_in_str(char *s, char c)
{
	int	res;

	res = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			res++;
		s++;
	}
	return (res);
}

static char	*ft_strdup_uc(char *s, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	res = ft_calloc(1 + i, sizeof(char));
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

static int	is_in_pattern(char *s, char c, char *pat)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (pat[j] && s[i] && s[i] != c)
	{
		if (pat[j] == '*')
		{
			j++;
			i++;
			while (s[i] && s[i] != c && s[i] != pat[j])
				i++;
		}
		else if (pat[j] == s[i])
		{
			j++;
			i++;
		}
		else
			break ;
	}
	if (!pat[j] && (!s[i] || s[i] == c))
		return (1);
	return (0);
}

char	**ft_split_pattern(char *s, char c, char *pat)
{
	int		i;
	int		k;
	char	**res;
	char	*tmp;

	i = 0;
	k = 0;
	res = ft_calloc(chrn_in_str(s, c) + 1, sizeof(char *));
	while (s[i])
	{
		tmp = &(s[i]);
		if (is_in_pattern(tmp, c, pat))
			res[k++] = ft_strdup_uc(tmp, c);
		while (s[i] && s[i] != c)
			i++;
		if (s[i] == c)
			i++;
	}
	if (k == 0)
	{
		free(res);
		res = NULL;
	}
	return (res);
}
