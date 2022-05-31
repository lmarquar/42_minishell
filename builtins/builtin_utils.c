/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:35:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/22 00:02:28 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const char *s)
{
	if (ft_strcmp_ci(s, "echo") == 1)
		return (1);
	else if (ft_strcmp(s, "cd") == 1)
		return (2);
	else if (ft_strcmp_ci(s, "pwd") == 1)
		return (3);
	else if (ft_strcmp(s, "export") == 1)
		return (4);
	else if (ft_strcmp(s, "unset") == 1)
		return (5);
	else if (ft_strcmp_ci(s, "env") == 1)
		return (6);
	else if (ft_strcmp(s, "exit") == 1)
		return (7);
	else
		return (0);
}

int	builtin_error(int error_code, char *builtin_name, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (error_code);
}
