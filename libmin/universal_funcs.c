#include "libmin.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (1);
	return (0);
}

int	ft_strcmp_ci(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_isalpha(*s1) && ft_isalpha(*s2))
		{
			if (*s1 + ' ' != *s2 && *s1 != *s2 + ' ' && *s1 != *s2)
				break ;
		}
		else if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (1);
	return (0);
}