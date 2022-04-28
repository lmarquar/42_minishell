/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_piping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:59:31 by lmarquar          #+#    #+#             */
/*   Updated: 2021/10/24 15:46:17 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipetopipe_rev(int fdf[], int fd[], char *arg, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fdf[1]);
		close(fdf[0]);
		close(fd[0]);
		close(fd[3]);
		return (createstream(fd[2], fd[1], arg));
	}
	return (0);
}

int	pipetopipe(int fdf[], int fd[], char *arg, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fdf[1]);
		close(fdf[0]);
		close(fd[1]);
		close(fd[2]);
		return (createstream(fd[0], fd[3], arg));
	}
	return (0);
}

int	infiletopipe(int fdf[], int fd[], char *arg, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fdf[1]);
		close(fd[0]);
		return (createstream(fdf[0], fd[1], arg));
	}
	return (0);
}

int	pipetooutfile(int fdf[], int fd[], char *arg, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fdf[0]);
		close(fd[1]);
		return (createstream(fd[0], fdf[1], arg));
	}
	return (0);
}
