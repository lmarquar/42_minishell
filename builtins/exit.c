#include "builtins.h"

static int	is_numeric(const char *s);

int	exec_exit(int exit_code, char **args, int is_pipeline)
{
	int	error;

	if (!is_pipeline)
		write(1, "exit\n", 5);
	if (!args || args[1] == NULL)
		exit(exit_code);
	if (!is_numeric(args[1]))
	{
		error = builtin_error(255, "exit", "numeric argument required");
		exit(error);
	}
	if (args[2] != NULL)
	{
		error = builtin_error(1, "exit", "too many arguments");
		return (error);
	}
	if (!is_pipeline)
		exit(ft_atoi(args[1]) % 256);
	return (ft_atoi(args[1]) % 256);
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
