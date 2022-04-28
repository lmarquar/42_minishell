/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_universal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <leon.marquardt@gmx.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:59:38 by lmarquar          #+#    #+#             */
/*   Updated: 2021/10/23 10:59:39 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	createstream(int fdin, int fdout, char *arg)
{
	char	**prog;
	char	*name;

	prog = ft_split(arg, ' ');
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(fdin);
	close(fdout);
	name = ft_strjoin("/usr/bin/", prog[0]);
	execve(name, prog, NULL);
	free(name);
	name = ft_strjoin("/bin/", prog[0]);
	execve(name, prog, NULL);
	free(name);
	exit(1);
	return (3);
}
