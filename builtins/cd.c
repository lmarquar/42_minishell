/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:24 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/31 17:11:50 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_cd(char *dir, char **cwd, t_env_var *env_var, int o_err_msg)
{
	int		i;
	int		i2;
	char	*curdir;

	if (!dir)
	{
		dir = find_in_env("HOME", 4, env_var);
		if (!dir)
			return (builtin_error(1, "cd", "HOME not set"));
	}
	i = chdir(dir);
	if (i == -1)
		return (builtin_error(1, "cd", strerror(errno)));
	i2 = 0;
	if (o_err_msg && i != -1)
		i2 = chdir(*cwd);
	if (i2 == -1 && o_err_msg)
		return (builtin_error(1, "cd", strerror(errno)));
	curdir = getcwd(NULL, 0);
	if (curdir)
	{
		free(*cwd);
		*cwd = curdir;
	}
	else
		perror("getcwd");
	return (0);
}
