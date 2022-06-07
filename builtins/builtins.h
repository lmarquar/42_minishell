/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 14:51:50 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <string.h>
# include <errno.h>

# include "../libft/libft.h"
# include "../env/env.h"
# include "../parser/parser.h"
# include "../libmin/libmin.h"

// utils

int	is_builtin(const char *s);

enum e_BUILTIN
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

// actual builtins

int	exec_env(int out, t_env_var *env, char **args);
int	exec_exit(t_bin *bin, char **args, int o_err_msg);
int	exec_pwd(const char *cwd, int fdout);
int	exec_cd(char *dir, char **cwd, t_env_var *env_var, int o_err_msg);
int	exec_export(int fdout, t_bin *bin, char **args, int o_err_msg);
int	exec_echo(int fdout, char **args);
int	exec_unset(char **unset_keys, t_bin *bin);

void	clean_exit(t_bin *bin, int exit_code);

#endif
