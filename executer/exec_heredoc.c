#include "execute.h"

static
void	exit_if_in_eq_delim(char *in, char *delim, t_bin *bin)
{
	if (!in)
		clean_exit(bin, 1);
	if (ft_strcmp(delim, in))
	{
		free(in);
		clean_exit(bin, 0);
	}
}

int	heredoc_handler(t_bin *bin, char *delim)
{
	char	*in;
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			in = readline("> ");
			exit_if_in_eq_delim(in, delim, bin);
			write(fd[1], in, ft_strlen(in));
			write(fd[1], "\n", 1);
			free(in);
		}
		clean_exit(bin, 1);
	}
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &bin->exit_code, 0);
	return (fd[0]);
}

int	dumb_heredoc_handler(t_bin *bin, char *delim)
{
	char	*in;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			in = readline("> ");
			exit_if_in_eq_delim(in, delim, bin);
			free(in);
		}
		clean_exit(bin, 1);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &bin->exit_code, 0);
	return (0);
}

int	heredoc_controller(t_bin *bin, t_list *redirs, char *name, int fd)
{
	if (contains_hdoc_or_in(redirs->next))
		dumb_heredoc_handler(bin, name);
	else
		fd = heredoc_handler(bin, name);
	return (fd);
}
