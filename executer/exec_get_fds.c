#include "execute.h"

int	contains_hdoc_or_in(t_list *redir)
{
	int	type;

	while (redir)
	{
		type = ((t_redir *)redir->content)->type;
		if (type == HEREDOC || type == INPUT)
			return (1);
		redir = redir->next;
	}
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

void	fdin_error(int type, char *name)
{
	if (type == INPUT)
		custom_error(-1, name, "No such file or directory");
	else if (type == HEREDOC)
		custom_error(-1, name, "heredoc execution failed");
}

int	el_handle_in_fd(t_bin *bin, t_list *redirs, int fd)
{
	int		fdtmp;
	char	*name;
	int		type;
	
	fdtmp = fd;
	while (contains_hdoc_or_in(redirs) && fdtmp != -1)
	{
		type = ((t_redir *)redirs->content)->type;
		name = ((t_redir *)redirs->content)->name;
		if (type == INPUT)
		{
			if (fdtmp != fd)
				close(fdtmp);
			fdtmp = open(name, O_RDONLY);
		}
		else if (type == HEREDOC)
		{
			if (fdtmp != fd)
				close(fdtmp);
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
	int	fd;

	fd = pipe_fd;
	while (redirs)
	{
		if (((t_redir *)redirs->content)->type == OUTPUT)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		else if (((t_redir *)redirs->content)->type == APPEND)
		{
			if (fd != STDOUT_FILENO)
				close(fd);
			fd = open(((t_redir *)redirs->content)->name, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		redirs = redirs->next;
	}
	return (fd);
}
