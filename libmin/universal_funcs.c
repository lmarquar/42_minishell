/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:57:06 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/08 16:07:38 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmin.h"

int	my_rl_go_on_nl(void)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	return (0);
}

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

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	size_t	i;

	i = 0;
	while (*s1 != c && *s2 != c)
	{
		if (*s1 == '\0' && *s2)
			return (-(unsigned char)*s2);
		if (*s1 && *s2 == '\0')
			return ((unsigned char)*s1);
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		i++;
	}
	if (*s1 == c && *s2)
		return (-(unsigned char)*s2);
	if (*s1 && *s2 == c)
		return ((unsigned char)*s1);
	return (0);
}

int	custom_error(int error_code, char *builtin_name, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (error_code);
}
