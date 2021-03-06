/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/08 17:37:09 by chelmerd         ###   ########.fr       */
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

// utils

int		is_builtin(const char *s);
void	clean_exit(t_bin *bin, int exit_code);

// actual builtins

int		exec_env(int out, t_env_var *env, char **args);
int		exec_exit(t_bin *bin, char **args, int o_err_msg);
int		exec_pwd(const char *cwd, int fdout);
int		exec_cd(char *dir, char **cwd, t_bin *bin, int o_err_msg);
int		exec_export(int fdout, t_bin *bin, char **args, int o_err_msg);
int		exec_echo(int fdout, char **args);
int		exec_unset(char **unset_keys, t_bin *bin);

#endif
