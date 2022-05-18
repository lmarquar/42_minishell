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

int	exec_cd(char *dir)
{
	int		i;
	char	*curdir;

	curdir = getcwd(NULL, 0);
	curdir = ft_strjoin(curdir, "/");
	if (dir[0] != '/')
		dir = get_full_path(curdir, dir);
	i = chdir(dir);
	if (i == -1)
		perror("chdir failed");
	return (0);
}