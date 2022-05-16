/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:02:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/12 13:09:34 by chelmerd         ###   ########.fr       */
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
		arr[i] = stringify(env, 1);
		env = env->next;
		i++;
	}
	return (arr);
}
