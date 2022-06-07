/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:57 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 14:58:04 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_pwd(const char *cwd, int fdout)
{
	if (!cwd)
		custom_error(1, "pwd", "internal PWD not set");
	write(fdout, cwd, ft_strlen(cwd));
	write(fdout, "\n", 1);
	return (0);
}
