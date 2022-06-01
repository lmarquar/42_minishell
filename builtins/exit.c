/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:54 by lmarquar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/31 17:23:09 by lmarquar         ###   ########.fr       */
=======
/*   Updated: 2022/06/01 11:44:45 by chelmerd         ###   ########.fr       */
>>>>>>> 2e827740ab600a96aafb6bca24d38731dea0f708
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline/readline.h"

static int		is_numeric(const char *s);
static void		clean_up(t_bin *bin);
static void		clean_exit(t_bin *bin, int exit_code);

/**
 * @brief exits the shell and returning the last exit_code or the first arg
 *
 * @param bin shell variables/state
 * @param args arguments: "exit" [n] - n is checked to be numeric
 * @param o_err_msg only error message: only check for errors but dont exit
 * @return int 2 if first argument is not numeric, 1 if too many arguments
 */
int	exec_exit(t_bin *bin, char **args, int o_err_msg)
{
	int	exit_code;

	if (!o_err_msg)
		write(1, "exit\n", 5);
	exit_code = bin->exit_code;
	if ((!args || !args[1]) && !o_err_msg)
		clean_exit(bin, exit_code);
	if ((!args || !args[1]) && o_err_msg)
		return (exit_code);
	if (!is_numeric(args[1]))
<<<<<<< HEAD
		error = builtin_error(255, "exit", "numeric argument required");
	else if (args[2] != NULL)
	{
		error = builtin_error(2, "exit", "numeric argument required");
		if (o_err_msg)
			return (error);
		clean_exit(bin, error);
	}
	error = ft_atoi(args[1]) % 256;
	if (args[2] && args[2][0])
=======
		exit_code = builtin_error(255, "exit", "numeric argument required");
	else if (args[2])
>>>>>>> 2e827740ab600a96aafb6bca24d38731dea0f708
		return (builtin_error(1, "exit", "too many arguments"));
	else
		exit_code = ft_atoi(args[1]) % 256;
	if (!o_err_msg)
		clean_exit(bin, exit_code);
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
