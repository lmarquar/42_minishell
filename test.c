/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:03 by chelmerd          #+#    #+#             */
/*   Updated: 2022/04/29 10:27:27 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SUCCESS 0

int	show_env_vars(t_env_var *env_vars)
{
	int	error;
	int	count;

	error = SUCCESS;
	count = 0;
	printf("Enviroment variables\n");
	if (!env_vars)
		return (ft_error("Null Pointer", 1));
	while (env_vars)
	{
		printf("%s=%s next=%p\n", env_vars->key, env_vars->val, env_vars->next);
		if (!env_vars->key || !env_vars->val)
			error = ft_error("Null Pointer", 2);
		env_vars = env_vars->next;
		count++;
	}
	printf("Total %d.\n", count);
	return (error);
}
