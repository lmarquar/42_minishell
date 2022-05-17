/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:40:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/17 18:03:01 by chelmerd         ###   ########.fr       */
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

void	add_env_var(t_env_var *lst, t_env_var *var)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = var;
}

void	remove_env_var(t_env_var *env, const char *key)
{
	size_t		key_len;
	t_env_var	*tmp;

	if (!env || !key)
		return ;
	key_len = ft_strlen(key);
	while (env->next && env->next->key
		&& ft_strncmp(env->next->key, key, key_len))
	{
		env = env->next;
	}
	tmp = env->next->next;
	clear_env_var(env->next);
	env->next = tmp;
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
