/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:02:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/10 12:30:11 by chelmerd         ###   ########.fr       */
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
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = cmd;
	}
	return (paths);
}

static
char	*stringify(t_env_var *env)
{
	char	*s;
	size_t	size;

	size = ft_strlen(env->key) + 1 + ft_strlen(env->val) + 1;
	s = ft_calloc(size, sizeof (char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, env->key, size);
	ft_strlcat(s, "=", size);
	ft_strlcat(s, env->val, size);
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
