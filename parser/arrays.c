/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:02:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/16 12:43:51 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		**create_path_arr(char *path, char *cwd);
char		**create_env_arr(t_env_var *env);

void		clear_pointer_arr(void **arr);
static char	*append_const_dir(char *path, char *cwd);

/**
 * @brief Create a null terminated array with directories to search binaries in.
 * This includes dirs from the $PATH, the CWD and the root.
 *
 * @param path value of $PATH
 * @param cwd the current working directory
 * @return char** array of directories (as strings ending with /)
 */
char	**create_path_arr(char *path, char *cwd)
{
	char	**paths;
	int		i;
	char	*tmp;

	tmp = append_const_dir(path, cwd);
	paths = ft_split(tmp, ':');
	if (tmp)
		free(tmp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		if (ft_strlen(paths[i]) == 1)
			break ;
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		if (!tmp)
		{
			clear_pointer_arr((void **) paths);
			return (NULL);
		}
		paths[i] = tmp;
	}
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

/*
* frees the array includind all the elements in it
*/
void	clear_pointer_arr(void **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static
char	*append_const_dir(char *path, char *cwd)
{
	char	*tmp;

	tmp = ft_strjoin(path, ":");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cwd);
	free(tmp);
	if (!path)
		return (NULL);
	tmp = ft_strjoin(path, ":/");
	free(path);
	return (tmp);
}
