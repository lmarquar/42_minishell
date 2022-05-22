#include "builtins.h"

static char	*get_full_path(char *cd, char *gd)
{
	int		i;
	char	*res;
	char	*tmp;

	res = ft_strjoin(cd, gd);
	i = 0;
	while (res[i])
		i++;
	if (res[--i] != '/')
	{
		tmp = res;
		res = ft_strjoin(res, "/");
		free(tmp);
	}
	free(cd);
	return (res);
}

int	exec_cd(char *dir, int o_err_msg)
{
	int		i;
	int		i2;
	char	*cwd;
	char	*curdir;

	if (!dir)
		return (0);
	cwd = getcwd(NULL, 0);
	curdir = ft_strjoin(cwd, "/");
	if (dir[0] != '/')
		dir = get_full_path(curdir, dir);
	i = chdir(dir);
	if (i == -1)
		perror("chdir failed");
	i2 = 0;
	if (o_err_msg && i != -1)
		i2 = chdir(cwd);
	if (i2 == -1 && o_err_msg)
		perror("chdir failed while undoing itself");
	return (0);
}