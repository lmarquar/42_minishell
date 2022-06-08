/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:12:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 16:10:05 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	is_valid_identifier_chr(int c, int pos);
static int	is_valid_key(char *s);

t_env_var	*new_env_var(char *key, char *value)
{
	t_env_var	*env;

	if (!key)
		return (NULL);
	if (!is_valid_key(key))
	{
		free(key);
		if (value)
			free(value);
		return (NULL);
	}
	env = malloc(sizeof (t_env_var));
	if (!env)
		return (NULL);
	env->key = key;
	env->val = value;
	env->next = NULL;
	return (env);
}

void	clear_env_var(t_env_var *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->val)
		free(env->val);
	free(env);
}

/*
* converts enviroment variable into a string with format: key=value
* if wrap_in_quotes is true than value will be wrapped in double quotes
*/
char	*stringify(t_env_var *env, int wrap_in_quotes)
{
	char	*s;
	size_t	size;

	if (!env->key)
		return (NULL);
	if (!env->val)
		size = ft_strlen(env->key) + 2;
	else
		size = ft_strlen(env->key) + 1 + ft_strlen(env->val) + 1;
	if (wrap_in_quotes && env->val)
		size += 2;
	s = ft_calloc(size, sizeof (char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, env->key, size);
	if (!env->val)
		return (s);
	ft_strlcat(s, "=", size);
	if (wrap_in_quotes)
		ft_strlcat(s, "\"", size);
	ft_strlcat(s, env->val, size);
	if (wrap_in_quotes)
		ft_strlcat(s, "\"", size);
	return (s);
}

static
int	is_valid_identifier_chr(int c, int pos)
{
	if (ft_isdigit(c) && pos == 0)
		return (0);
	else if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static
int	is_valid_key(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!is_valid_identifier_chr(s[i], i))
			return (0);
		i++;
	}
	return (1);
}
