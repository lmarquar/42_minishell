/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/17 17:08:36 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>

# include "../libft/libft.h"
# include "../env/env.h"

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

#endif
