/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:54 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/31 11:17:26 by chelmerd         ###   ########.fr       */
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
	if (!is_numeric(args[1]))
		clean_exit(bin, builtin_error(2, "exit", "numeric argument required"));
	error = ft_atoi(args[1]) % 256;
	if (args[2] && args[2][0])
	{
		return (builtin_error(1, "exit", "too many arguments"));
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
	if (!s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s && ft_isdigit(*s))
	{
		s++;
	}
	if (*s == '\0')
		return (1);
	return (0);
}
