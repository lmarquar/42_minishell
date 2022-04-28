/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaderi <mnaderi@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:59:19 by lmarquar          #+#    #+#             */
/*   Updated: 2021/10/26 18:46:38 by mnaderi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
int	initvars(int fdf[], char *env[], int argc, char *argv[])
{
	fdf[0] = open(argv[1], O_RDONLY);
	fdf[1] = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	if ((access(argv[1], R_OK) + access(argv[argc - 1], W_OK)) != 0)
	{
		perror("Input file does not exist!\n");
		return (1);
	}
	env[0] = "/bin/";
	env[1] = "/usr/bin/";
	env[2] = 0;
	return (0);
}

static
int	writetofile(int fdin, int fdout)
{
	char	c;
	int		i;

	while (read(fdout, &c, 1) > 0)
		;
	i = read(fdin, &c, 1);
	while (i > 0)
	{
		write(fdout, &c, 1);
		i = read(fdin, &c, 1);
	}
	return (0);
}

static
int	doublecommand(int fdf[], int fd[], char *argv[], int *pid)
{
	int	i;

	i = 3;
	if (pipe(&(fd[2])) == -1)
		return (3);
	pipetopipe(fdf, fd, argv[i], &(pid[1]));
	close(fd[0]);
	close(fd[1]);
	i++;
	if (pipe(fd) == -1)
		return (3);
	pipetopipe_rev(fdf, fd, argv[i], &(pid[2]));
	close(fd[2]);
	close(fd[3]);
	return (0);
}

static
int	closeandwait(int fd[], int fdf[], int *pid)
{
	int	i;
	int	x;

	close(fd[0]);
	close(fdf[0]);
	close(fdf[1]);
	i = -1;
	while (++i < 3)
	{
		x = 0;
		waitpid(-1, &x, 0);
		if (x != 0 && x != 256)
			perror("cp");
	}
	free(pid);
	return (0);
}

int	bonus_append(int argc, char *argv[])
{
	char	*env[3];
	int		fdf[2];
	int		*pid;
	int		fd[4];
	char	*limit;

	if (initvars(fdf, env, argc, argv) != 0)
		return (1);
	pid = malloc(sizeof(int) * (argc - 2));
	pid[argc - 3] = 0;
	if (pipe(fd) == -1)
		return (3);
	limit = ft_strjoin("grep -v ", argv[2]);
	infiletopipe(fdf, fd, limit, &(pid[0]));
	free(limit);
	if (doublecommand(fdf, fd, argv, pid) != 0)
		return (3);
	close(fd[1]);
	writetofile(fd[0], fdf[1]);
	closeandwait(fd, fdf, pid);
	return (0);
}
