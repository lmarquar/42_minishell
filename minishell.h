/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:29:16 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/02 13:31:24 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMT "minishell>"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "pipex/pipex.h"
# include "parser.h"

typedef struct s_env_var
{
	char				*key;
	char				*val;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_bin
{
	char		*in;
	int			is_builtin;
	char		*cmd;
	char		**args;
	t_env_var	*env;
	int			exit_code;
}	t_bin;

int	execute(t_cmd_line *cmd_line, t_env_var *env_vars);

#endif
