#include "bonus.h"

char	*file_to_str(char *name)
{
	int		i;
	int		j;
	int		fd;
	char	*res;

	res = ft_calloc(500, sizeof(char));
	fd = open(name, O_RDONLY);
	i = read(fd, res, 1);
	j = 0;
	while (++j < 500)
	{
		i = read(fd, &(res[j]), 1);
		if (i <= 0 || res[j] == EOF)
		{
			res[j] = 0;
			break ;
		}
	}
	return (res);
}

int	full_path_exec(int fd, char *name, char **args)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		return (1);
	}
	close(fd);
	execve(name, args, NULL);
	perror("execve failed in wildcard func");
	return (1);
}

char	*ls_to_str(void)
{
	char	*out;
	char	*tmp_file;
	int		fd;
	int		pid;
	char	**args;

	tmp_file = "ls_out";
	fd = open(tmp_file, O_RDWR | O_CREAT, 0777);
	args = ft_calloc(2, sizeof(char *));
	args[0] = "ls";
	pid = fork();
	if (pid == 0)
		full_path_exec(fd, "/bin/ls", args);
	close(fd);
	if (waitpid(pid, &fd, 0) == -1)
	{
		perror("waitpid failed hopefully due to active debugging");
		waitpid(pid, &fd, 0);
	}
	free(args);
	out = file_to_str(tmp_file);
	unlink(tmp_file);
	return (out);
}

char	**replace_ast_bonus(char *s)
{
	int		i;
	char	*ls_out;
	char	**res;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			break ;
		i++;
	}
	if (!s[i])
		return (NULL);
	ls_out = ls_to_str();
	res = ft_split_pattern(ls_out, '\n', s);
	printf("%s\n", ls_out);
	free(ls_out);
	return (res);
}