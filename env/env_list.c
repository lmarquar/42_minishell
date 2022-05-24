/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:40:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/24 13:49:47 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// returns the length of the list of enviroment variabels
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

t_env_var	*add_env_var(t_env_var **lst, t_env_var *var)
{
	t_env_var	*e;

	e = *lst;
	if (!e)
	{
		*lst = var;
		return (var);
	}
	while (e->next)
	{
		e = e->next;
	}
	e->next = var;
	return (var);
}

/**
 * @brief remove and frees the enviroment variable that correspond to key
 * 
 * @param env the list of env_vars (NON-NULL)
 * @param key the key to look for (NON-NULL) [key=value, next]
 * @return t_env_var* the list of env_vars (could be NULL)
 */
t_env_var	*remove_env_var(t_env_var *env, const char *key)
{
	size_t		key_len;
	t_env_var	*tmp;
	t_env_var	*start;

	start = env;
	key_len = ft_strlen(key);
	if (env && env->key && !ft_strncmp(env->key, key, key_len + 1))
	{
		tmp = env->next;
		clear_env_var(env);
		return (tmp);
	}
	while (env->next && env->next->key
		&& ft_strncmp(env->next->key, key, key_len + 1))
	{
		env = env->next;
	}
	if (!env->next)
		return (start);
	tmp = env->next->next;
	clear_env_var(env->next);
	env->next = tmp;
	return (start);
}

void	clear_env_vars(t_env_var *lst)
{
	t_env_var	*next;

	while (lst)
	{
		next = lst->next;
		clear_env_var(lst);
		lst = next;
	}
}

char	*find_in_env(char *key, size_t key_len, t_env_var *env_vars)
{
	while (env_vars
		&& (key_len != ft_strlen(env_vars->key)
			|| ft_strncmp(env_vars->key, key, key_len) != 0))
	{
		env_vars = env_vars->next;
	}
	if (env_vars)
		return (env_vars->val);
	return (NULL);
}
