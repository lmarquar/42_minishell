/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:54 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/25 17:00:09 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline/readline.h"

static int		is_numeric(const char *s);
static void		clean_up(t_bin *bin);
static void		clean_exit(t_bin *bin, int exit_code);

int	exec_exit(t_bin *bin, char **args, int o_err_msg)
{
	int	error;
	int	exit_code;

	if (!o_err_msg)
		write(1, "exit\n", 5);
	exit_code = bin->exit_code;
	if ((!args || args[1] == NULL) && !o_err_msg)
		clean_exit(bin, exit_code);
	error = ft_atoi(args[1]) % 256;
	if (!is_numeric(args[1]))
		error = builtin_error(255, "exit", "numeric argument required");
	if (args[2] != NULL)
	{
		error = builtin_error(1, "exit", "too many arguments");
		return (error);
	}
	if (!o_err_msg)
		clean_exit(bin, error);
	return (exit_code);
}

static void	clean_exit(t_bin *bin, int exit_code)
{
	clean_up(bin);
	exit(exit_code);
}

static void	clean_up(t_bin *bin)
{
	if (bin->in)
		free(bin->in);
	if (bin->cwd)
		free(bin->cwd);
	if (bin->env)
		clear_env_vars(bin->env);
	if (bin->env_arr)
		clear_pointer_arr(&bin->env_arr);
	if (bin->paths)
		clear_pointer_arr(&bin->paths);
	if (bin->cmd_line)
		clear_cmd_line(bin->cmd_line);
	if (bin->pid)
		free(bin->pid);
	rl_clear_history();
	free(bin);
}

static int	is_numeric(const char *s)
{
	while (s && *s && ft_isdigit(*s))
	{
		s++;
	}
	if (*s == '\0')
		return (1);
	return (0);
}
