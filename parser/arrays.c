/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:02:58 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/25 16:58:59 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**create_path_arr(char *path);
char	**create_env_arr(t_env_var *env);

void	clear_pointer_arr(char ***arr);

/**
 * @brief Create a null terminated array with directories to search binaries in.
 * This includes dirs from the $PATH, the CWD and the root.
 *
 * @param path value of $PATH
 * @return char** array of directories (as strings ending with /)
 */
char	**create_path_arr(char *path)
{
	char	**paths;
	int		i;
	char	*tmp;

	paths = ft_split(path, ':');
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
			clear_pointer_arr(&paths);
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
		arr[i] = stringify(env, 0);
		env = env->next;
		i++;
	}
	return (arr);
}

t_smp_cmd	**create_cmd_arr(t_list *cmd_lst)
{
	t_smp_cmd	**arr;
	size_t		len;
	size_t		i;

	len = ft_lstsize(cmd_lst);
	arr = ft_calloc(len + 1, sizeof (t_smp_cmd *));
	if (!arr)
		return (NULL);
	i = 0;
	while (cmd_lst)
	{
		arr[i++] = (t_smp_cmd *) cmd_lst->content;
		cmd_lst = cmd_lst->next;
	}
	return (arr);
}

/*
* frees the array including all the elements in it
*/
void	clear_pointer_arr(char ***arr)
{
	size_t	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}
