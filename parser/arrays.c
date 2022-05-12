/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:02:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/12 11:47:38 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**create_path_arr(char *path, char *cwd)
{
	char	**paths;
	int		i;
	char	*cmd;
	char	*tmp;

	tmp = ft_strjoin(path, ":");
	path = ft_strjoin(tmp, cwd);
	free(tmp);
	paths = ft_split(path, ':');
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = cmd;
	}
	free(path);
	return (paths);
}

/*
* converts enviroment variable into a string with format: key="value"
*/
static
char	*stringify(t_env_var *env)
{
	char	*s;
	size_t	size;

	if (!env->key || !env->val)
		return (NULL);
	size = ft_strlen(env->key) + 3 + ft_strlen(env->val) + 1;
	s = ft_calloc(size, sizeof (char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, env->key, size);
	ft_strlcat(s, "=", size);
	ft_strlcat(s, "\"", size);
	ft_strlcat(s, env->val, size);
	ft_strlcat(s, "\"", size);
	return (s);
}

size_t	env_var_len(t_env_var *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

char	**create_env_arr(t_env_var *env)
{
	char	**arr;
	size_t	i;

	arr = ft_calloc(env_var_len(env) + 1, sizeof (char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = stringify(env);
		env = env->next;
		i++;
	}
	return (arr);
}

t_env_var	*get_env_from_str(char *env_str)
{
	t_env_var	*env;
	size_t		key_size;
	char		*val;

	env = malloc(sizeof (t_env_var));
	val = ft_strnstr(env_str, "=", ft_strlen(env_str)) + 1;
	key_size = val - env_str;
	env->key = ft_calloc(key_size, sizeof (char));
	ft_strlcpy(env->key, env_str, key_size);
	env->val = ft_strdup(val);
	env->next = NULL;
	return (env);
}
