/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:24 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 17:48:35 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_cd(char *dir, char **cwd, t_env_var *env_var, int o_err_msg)
{
	int		i;
	char	*curdir;

	if (!dir)
		dir = find_in_env("HOME", 4, env_var);
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
	}
	else
		perror("getcwd");
	return (0);
}
