#include "execute.h"

void	fdin_error(int type, char *name)
{
	if (type == INPUT)
		custom_error(-1, name, "No such file or directory");
	else if (type == HEREDOC)
		custom_error(-1, name, "heredoc execution failed");
}

int	get_in_fd(t_bin *bin, t_list *redirs, int fd)
{
	int		fdtmp;
	char	*name;
	int		type;

	fdtmp = fd;
	while (contains_hdoc_or_in(redirs) && fdtmp != -1)
	{
		type = ((t_redir *)redirs->content)->type;
		name = ((t_redir *)redirs->content)->name;
		if ((type == INPUT || type == HEREDOC) && fdtmp != fd)
			close(fdtmp);
		if (type == INPUT)
			fdtmp = open(name, O_RDONLY);
		else if (type == HEREDOC)
		{
			fdtmp = heredoc_controller(bin, redirs, name, fdtmp);
			if (bin->exit_code == 2)
				return (-1);
		}
		redirs = redirs->next;
	}
	if (fdtmp == -1)
		fdin_error(type, name);
	return (fdtmp);
}

int	get_out_fd(t_list *redirs, int pipe_fd)
{
	int		fd;
	int		type;
	char	*name;

	fd = pipe_fd;
	while (redirs)
	{
		type = ((t_redir *)redirs->content)->type;
		name = ((t_redir *)redirs->content)->name;
		if (type == OUTPUT)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		else if (type == APPEND)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(name, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		redirs = redirs->next;
	}
	return (fd);
}
