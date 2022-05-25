/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:45 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/25 13:44:00 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/**
 * @brief writes the arguments to the given filedescriptor
 * 
 * @param fdout default stdout
 * @param args options (-n for no newline) and arguments
 * @return always int 0
 */
int	exec_echo(int fdout, char **args)
{
	int		i;

	i = 1;
	if (!args[i])
	{
		write(fdout, "\n", 1);
		return (0);
	}
	while (args[i] && !ft_strncmp(args[i], "-n", 3))
		i++;
	while (args[i])
	{
		write(fdout, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(fdout, " ", 1);
	}
	if (ft_strncmp(args[1], "-n", 3))
		write(fdout, "\n", 1);
	return (0);
}
