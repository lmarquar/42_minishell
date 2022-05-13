/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:35:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/09 15:38:10 by chelmerd         ###   ########.fr       */
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
