#include "execute.h"

void	close_ifn_inout(int fd)
{
	if (fd != STDOUT_FILENO && fd != STDIN_FILENO)
		close(fd);
}

int	exec_in_to_pipe(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	if (pipe(&(fd[0])) == -1)
		return (3);
	if (bin->cmd_line->heredoc_delimiter)
	{
		heredoc_handler(bin->cmd_line, fd[1]);
		(*i)[1] = (*i)[1] - 1;
	}
	else if (bin->cmd_line->simple_commands[0]->is_builtin)
	{
		exec_builtin(bin, bin->cmd_line->simple_commands[0]->args, fd[4], fd[1]);
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close_ifn_inout(fd[5]);
			close(fd[0]);
			exec_el(bin->cmd_line->simple_commands[0]->args, bin, fd[4], fd[1]);
		}
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(**i)++;
	}
	return (0);
}

int	exec_pipe1_to_pipe2(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	close(fd[1]);
	if (pipe(&(fd[2])) == -1)
		return (3);
	if (bin->cmd_line->simple_commands[0]->is_builtin)
	{
		exec_builtin(bin, bin->cmd_line->simple_commands[0]->args, fd[0], fd[3]);
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close(fd[2]);
			close_ifn_inout(fd[5]);
			close_ifn_inout(fd[4]);
			exec_el(bin->cmd_line->simple_commands[0]->args, bin, fd[0], fd[3]);
		}
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(**i)++;
	}
	close(fd[0]);
	return (0);
}

int	exec_pipe2_to_pipe1(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	if (pipe(&(fd[0])) == -1)
		return (3);
	close(fd[3]);
	if (bin->cmd_line->simple_commands[0]->is_builtin)
	{
		exec_builtin(bin, bin->cmd_line->simple_commands[0]->args, fd[2], fd[1]);
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(*i)[1] = (*i)[1] - 1;
	}
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close(fd[0]);
			close_ifn_inout(fd[5]);
			close_ifn_inout(fd[4]);
			exec_el(bin->cmd_line->simple_commands[0]->args, bin, fd[2], fd[1]);
		}
		bin->cmd_line->simple_commands = bin->cmd_line->simple_commands + 1;
		(**i)++;
	}
	close(fd[2]);
	return (0);
}

int	exec_pipe_to_out(t_bin *bin, int *pid, int fd[], size_t (*i)[])
{
	int	i_fd;

	i_fd = 0;
	if (!(bin->cmd_line->pipe_count % 2))
		i_fd = 2;
	close(fd[1 + i_fd]);
	if (bin->cmd_line->append > 0)
	{
		append(fd[i_fd], fd[5]);
		((*i)[1])--;
	}
	else if (bin->cmd_line->simple_commands[0]->is_builtin)
		exec_builtin(bin, bin->cmd_line->simple_commands[0]->args, fd[i_fd], fd[5]);
	else
	{
		pid[**i] = fork();
		if (pid[**i] == 0)
		{
			close_ifn_inout(fd[4]);
			exec_el(bin->cmd_line->simple_commands[0]->args, bin, fd[i_fd], fd[5]);
		}
	}
	close(fd[i_fd]);
	return (0);
}

int	exec_with_pipes(t_bin *bin, int *pid, int fd[])
{
	size_t	i[2];

	i[0] = 0;
	i[1] = bin->cmd_line->pipe_count;
	exec_in_to_pipe(bin, pid, fd, &i);
	while (i[0] < i[1])
	{
		exec_pipe1_to_pipe2(bin, pid, fd, &i);
		if (i[0] >= i[1])
			break ;
		exec_pipe2_to_pipe1(bin, pid, fd, &i);
	}
	exec_pipe_to_out(bin, pid, fd, &i);
	close_ifn_inout(fd[4]);
	close_ifn_inout(fd[5]);
	return (0);
}
