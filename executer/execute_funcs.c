#include "execute.h"

static int	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

int	handle_dup2error()
{
	perror("dup2 failed(system error)\n");
	return (1);
}

int	exec_el(char **arg, char **paths, int fdin, int fdout)
{
	int	i;
	char	*cmd;

	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) < 0);
			return (handle_dup2error())
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) < 0);
			return (handle_dup2error())
		close(fdout);
	}
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, arg[0]);
		execve(cmd, arg, NULL);
		free(cmd);
	}
	printf("Command couldn't be found\n");
	free_arr(paths);
	exit(1);
	return (0);
}

int append(int fdin, int fdout)
{
	char	c;
	int		i;

	while (read(fdout, &c, 1) > 0)
		;
	i = read(fdin, &c, 1);
	while (i > 0)
	{
		write(fdout, &c, 1);
		i = read(fdin, &c, 1);
	}
	return (0);
}

int	heredoc_handler(t_cmd_line *cmd_line, int fdout)
{
	char	*in;
	char	*term;
	char	*delimiter;
	int		p_count;

	delimiter = cmd_line->heredoc_delimiter;
	p_count = cmd_line->pipe_count;
	if (cmd_line->heredoc_delimiter)
		p_count--;
	if (cmd_line->append > 0)
		p_count--;
	term = "heredoc>";
	if (p_count-- > 0)
		term = ft_strjoin("pipe ", term);
	while (p_count-- > 0)
	{
		in = ft_strjoin("pipe ", term);
		free(term);
		term = in;
	}
	while(1)
	{
		in = readline(term);
		if (!ft_strncmp(delimiter, in, ft_strlen(in)))
				break ;
		write(fdout, in, ft_strlen(in));
		write(fdout, "\n", 1);
	}
	return (0);
}
