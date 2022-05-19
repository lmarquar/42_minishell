/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/19 23:08:14y lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>

# include "../libft/libft.h"
# include "../env/env.h"
# include "../parser/parser.h"

// utils

int	is_builtin(const char *s);
int	builtin_error(int error_code, char *builtin_name, char *msg);

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
// echo
// cd
// pwd
// export
// unset
// env
int	exec_env(int out, t_env_var *env, char **args);
// exit
int	exec_exit(t_bin *bin, char **args, int o_err_msg);
int	exec_pwd(int fdout);
int	exec_cd(char *dir, int o_err_msg);
int	exec_export(int fdout, t_bin *bin, char *var_ass, int o_err_msg);
int	exec_echo(int fdout, char **args);
int exec_unset(char *unset_key, t_bin *bin);

#endif
