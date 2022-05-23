#include "builtins.h"

int	exec_cd(char *dir, char **cwd, int o_err_msg)
{
	int		i;
	int		i2;
	char	*curdir;

	if (!dir)
		return (builtin_error(2, "cd", "no releatic or abolute path found"));
	i = chdir(dir);
	if (i == -1)
	{
		return (builtin_error(1, "cd", strerror(errno)));
	}
	i2 = 0;
	if (o_err_msg && i != -1)
		i2 = chdir(*cwd);
	if (i2 == -1 && o_err_msg)
		return (builtin_error(1, "cd", strerror(errno)));
	curdir = getcwd(NULL, 0); // refresh the cwd
	if (curdir)
	{
		free(*cwd);
		*cwd = curdir;
	}
	else
		perror("getcwd");
	return (0);
}