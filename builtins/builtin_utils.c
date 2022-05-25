/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:35:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/25 16:38:21 by chelmerd         ###   ########.fr       */
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

int	builtin_error(int error_code, char *builtin_name, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (error_code);
}
