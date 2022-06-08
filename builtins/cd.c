/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:24 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/08 17:42:25 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char *cwd, t_bin *bin);

int	exec_cd(char *dir, char **cwd, t_bin *bin, int o_err_msg)
{
	int		i;
	char	*curdir;

	if (!dir)
		dir = find_in_env("HOME", 4, bin->env);
	if (!dir)
		return (custom_error(1, "cd", "HOME not set"));
	i = chdir(dir);
	if (i == -1)
		return (custom_error(1, "cd", strerror(errno)));
	i = 0;
	if (o_err_msg)
		i = chdir(*cwd);
	if (i == -1 && o_err_msg)
		return (custom_error(1, "cd", strerror(errno)));
	curdir = getcwd(NULL, 0);
	if (curdir)
	{
		free(*cwd);
		*cwd = curdir;
		update_pwd(*cwd, bin);
	}
	else
		perror("getcwd");
	return (0);
}

static
void	update_pwd(char *cwd, t_bin *bin)
{
	char	**args;
	char	*p;
	size_t	size;

	size = ft_strlen(cwd) + ft_strlen("PWD") + 2;
	args = ft_calloc(2, sizeof (char *));
	p = ft_calloc(size, sizeof (char));
	ft_strlcpy(p, "PWD=", size);
	ft_strlcat(p, cwd, size);
	args[0] = p;
	exec_export(1, bin, args, 0);
	free(args);
	free(p);
}
