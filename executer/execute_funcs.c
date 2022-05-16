#include "execute.h"

int	handle_dup2error(void)
{
	perror("dup2 failed(system error)\n");
	return (1);
}

int	append(int fdin, int fdout)
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
	while (1)
	{
		in = readline(term);
		if (!ft_strncmp(delimiter, in, ft_strlen(in)))
			break ;
		write(fdout, in, ft_strlen(in));
		write(fdout, "\n", 1);
	}
	return (0);
}
