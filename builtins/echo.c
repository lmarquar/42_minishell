#include "builtins.h"

int	exec_echo(int fdout, char **args)
{
	int		i;

	i = 1;
	if (!args[i])
		return (0);
	while (!ft_strncmp(args[i], "-n", 2))
		i++;
	while (args[i])
	{
		write(fdout, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(args[1], "-n", 2))
		write(1, "\n", 1);
	return (0);
}
