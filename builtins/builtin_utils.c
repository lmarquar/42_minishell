/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:35:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 14:53:27 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const char *s)
{
	if (ft_strcmp_ci(s, "echo") == 1)
		return (ECHO);
	else if (ft_strcmp(s, "cd") == 1)
		return (CD);
	else if (ft_strcmp_ci(s, "pwd") == 1)
		return (PWD);
	else if (ft_strcmp(s, "export") == 1)
		return (EXPORT);
	else if (ft_strcmp(s, "unset") == 1)
		return (UNSET);
	else if (ft_strcmp_ci(s, "env") == 1)
		return (ENV);
	else if (ft_strcmp(s, "exit") == 1)
		return (EXIT);
	else
		return (0);
}
