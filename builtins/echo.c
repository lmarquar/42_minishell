/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:45 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 11:08:27 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	skip_n_flags(char **args)
{
	int	i;
	int	k;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		k = 1;
		while (args[i][k] == 'n')
			k++;
		if (!args[i][k])
		{
			i++;
		}
		else
			break ;
	}
	return (i);
}

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
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (!args[i])
	{
		write(fdout, "\n", 1);
		return (0);
	}
	i = skip_n_flags(args);
	if (i > 1)
		n_flag = 1;
	while (args[i])
	{
		write(fdout, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(fdout, " ", 1);
	}
	if (!n_flag)
		write(fdout, "\n", 1);
	return (0);
}
