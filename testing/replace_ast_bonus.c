#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

char	*ls_to_string(void)
{
	char	*out;
	char	tmp_file;
	int		fd;
	int		pid;
	char	**args;
	
	tmp_file = "ls_out";
	fd = open(tmp_file, O_RDWR | O_CREAT, 0777);
	args = ft_calloc(2, sizeof(char *));
	args[0] = "ls";
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (handle_dup2error());
		close(fd);
		execve("/bin/ls", args, NULL);
	}
}

char	**replace_ast_bonus(char *s)
{
	int 	i;
	int 	j;
	char	*ls_out;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			break ;
	}
	if (!s[i])
		return (0);
	ls_out = ls_to_string();
	printf("%s\n", ls_out);
	return (0);
}