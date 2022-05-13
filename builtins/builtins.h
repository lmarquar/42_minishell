/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:23 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/13 11:15:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>

# include "../libft/libft.h"
# include "../env/env.h"

// utils

int	is_builtin(const char *s);

enum e_BUILTIN
{
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 6
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

#endif
