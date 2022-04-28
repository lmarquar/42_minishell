/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:59:44 by lmarquar          #+#    #+#             */
/*   Updated: 2022/04/28 11:05:02 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
int	bon_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (0);
	else
		return (1);
}

static
int	initvars(int fdf[], char *env[], int argc, char *argv[])
{
	if (access(argv[1], R_OK) != 0)
	{
		perror(argv[1]);
		return (1);
	}
	fdf[0] = open(argv[1], O_RDONLY);
	unlink(argv[argc - 1]);
	fdf[1] = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	env[0] = "/bin/";
	env[1] = "/usr/bin/";
	env[2] = 0;
	return (0);
}

static
int	pipeloop(int fdf[], int fd[], char *argv[], int *pid)
{
	int	argc;
	int	i;

	argc = 0;
	i = 3;
	while (argv[argc])
		argc++;
	while (i < (argc - 2))
	{
		if (pipe(&(fd[2])) == -1)
			return (3);
		pipetopipe(fdf, fd, argv[i], &(pid[i - 2]));
		close(fd[0]);
		close(fd[1]);
		i++;
		if (i == (argc - 2))
			break ;
		if (pipe(fd) == -1)
			return (3);
		pipetopipe_rev(fdf, fd, argv[i], &(pid[i - 2]));
		close(fd[2]);
		close(fd[3]);
		i++;
	}
	return (0);
}

static
int	closeandwait(int fd[], int fdf[], int pid[], int argc)
{
	int	i;
	int	s;

	i = -1;
	if ((argc % 2) == 0)
	{
		close(fd[3]);
		close(fd[4]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	close(fdf[0]);
	close(fdf[1]);
	while (++i < (argc - 3))
	{
		s = 0;
		waitpid(pid[i], &s, 0);
		if (s != 0 && s != 256)
			perror("cp");
	}
	free(pid);
	return (0);
}

int	pipex(int argc, char *argv[])
{
	int		fdf[2];
	int		fd[4];
	int		*pid;
	char	*env[3];

	if (argc == 6 && !bon_strcmp(argv[1], "here_doc"))
		return (bonus_append(argc, argv));
	if (initvars(fdf, env, argc, argv) != 0)
		return (1);
	pid = malloc(sizeof(int) * (argc - 2));
	pid[argc - 3] = 0;
	if (pipe(fd) == -1)
		return (3);
	infiletopipe(fdf, fd, argv[2], &(pid[0]));
	if (pipeloop(fdf, fd, argv, pid) != 0)
		return (3);
	if (argc % 2 == 0)
		pipetooutfile(fdf, &(fd[2]), argv[argc - 2], &(pid[argc - 4]));
	else
		pipetooutfile(fdf, fd, argv[argc - 2], &(pid[argc - 4]));
	closeandwait(fd, fdf, pid, argc);
	return (0);
}
