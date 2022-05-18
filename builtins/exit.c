#include "builtins.h"
#include "readline/readline.h"

static int		is_numeric(const char *s);
static void		clean_up(t_bin *bin);
static void		clean_exit(t_bin *bin, int exit_code);

int	exec_exit(t_bin *bin, char **args, int is_pipeline)
{
	int	error;
	int	exit_code;

	if (!is_pipeline)
		write(1, "exit\n", 5);
	exit_code = bin->exit_code;
	if (!args || args[1] == NULL)
		clean_exit(bin, exit_code);
	if (!is_numeric(args[1]))
	{
		error = builtin_error(255, "exit", "numeric argument required");
		clean_exit(bin, error);
	}
	if (args[2] != NULL)
	{
		error = builtin_error(1, "exit", "too many arguments");
		return (error);
	}
	if (!is_pipeline)
		clean_exit(bin, ft_atoi(args[1]) % 256);
	return (ft_atoi(args[1]) % 256);
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
		clear_pointer_arr((void **) bin->env_arr);
	if (bin->paths)
		clear_pointer_arr((void **) bin->paths);
	if (bin->cmd_line)
		clear_cmd_line(bin->cmd_line);
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
