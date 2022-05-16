/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:35:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/16 15:25:33 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const char *s)
{
	if (ft_strncmp(s, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(s, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(s, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(s, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(s, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(s, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(s, "exit", 5) == 0)
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
