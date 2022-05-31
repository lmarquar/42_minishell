/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:00 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/29 14:10:48 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_unset(char **unset_keys, t_bin *bin)
{
	t_env_var	*env;
	int			i;

	env = bin->env;
	if (!env || !*unset_keys)
		return (0);
	i = -1;
	while (unset_keys[++i])
		bin->env = remove_env_var(env, unset_keys[i]);
	return (0);
}
