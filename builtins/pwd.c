#include "builtins.h"

int	exec_pwd(const char *cwd, int fdout)
{
	if (!cwd)
		builtin_error(1, "pwd", "internal PWD not set");
	write(fdout, cwd, ft_strlen(cwd));
	write(fdout, "\n", 1);
	return (0);
}