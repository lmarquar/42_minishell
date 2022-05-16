/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:12:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/12 13:13:31 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_var	*new_env_var(char *key, char *value)
{
	t_env_var	*env;

	if (!key)
		return (NULL);
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

	if (!env->key || !env->val)
		return (NULL);
	size = ft_strlen(env->key) + 1 + ft_strlen(env->val) + 1;
	if (wrap_in_quotes)
		size += 2;
	s = ft_calloc(size, sizeof (char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, env->key, size);
	ft_strlcat(s, "=", size);
	if (wrap_in_quotes)
		ft_strlcat(s, "\"", size);
	ft_strlcat(s, env->val, size);
	if (wrap_in_quotes)
		ft_strlcat(s, "\"", size);
	return (s);
}

t_env_var	*get_env_from_str(char *env_str)
{
	char		*key;
	size_t		key_size;
	char		*val;
	char		*val_ptr;

	if (!env_str)
		return (NULL);
	val_ptr = ft_strnstr(env_str, "=", ft_strlen(env_str)) + 1;
	if (!val_ptr)
		return (NULL);
	key_size = val_ptr - env_str;
	key = ft_calloc(key_size, sizeof (char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, key_size);
	val = ft_strdup(val_ptr);
	if (!val)
	{
		free(key);
		return (NULL);
	}
	return (new_env_var(key, val));
}
