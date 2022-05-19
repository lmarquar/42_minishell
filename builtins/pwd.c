#include "builtins.h"

int	exec_pwd(int fdout)
{
	char	*s;

	s = getcwd(NULL, 0);
	write(fdout, s, ft_strlen(s));
	return (0);
}