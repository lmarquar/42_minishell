/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:54:00 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/25 12:54:01 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_unset(char *unset_key, t_bin *bin)
{
	t_env_var	*env;

	env = bin->env;
	if (!env || !unset_key)
		return (0);
	bin->env = remove_env_var(env, unset_key);
	return (0);
}
