/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:48 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/31 15:07:45 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_env(int out, t_env_var *env, char **args)
{
	if (args && args[1])
		ft_putendl_fd("WARNNG: options and arguments are ignored.", 2);
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(env->key, out);
			ft_putstr_fd("=", out);
			ft_putendl_fd(env->val, out);
		}
		env = env->next;
	}
	return (0);
}
