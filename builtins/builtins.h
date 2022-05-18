/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/18 12:39:29 by leon             ###   ########.fr       */
=======
/*   Updated: 2022/05/18 12:48:47 by chelmerd         ###   ########.fr       */
>>>>>>> origin/parser
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
int	exec_exit(int exit_code, char **args, int is_pipeline);
int	exec_pwd(int fdout);
int	exec_cd(char *dir);
int	exec_export(int fdout, t_bin *bin, char *var_ass);
int	exec_echo(int fdout, char **args);
int exec_unset(char *unset_key, t_bin *bin);


#endif
