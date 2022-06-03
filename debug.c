#include "minishell.h"

void	print_redirs(t_list *redirs)
{
	t_redir *r;
	char	*redir_type;

	if (!redirs)
		printf("No redirections");
	while (redirs)
	{
		r = (t_redir *) redirs->content;
		if (redir_type == INPUT)
			redir_type = "INPUT";
		else if (redir_type == HEREDOC)
			redir_type = "HERDOC";
		else if (redir_type == OUTPUT)
			redir_type = "OUTPUT";
		else if (redir_type == APPEND)
			redir_type = "APPEND";
		else
			redir_type = "UNKOWN"
		printf("type=%s, name=%s\n", r->type, r->name);
		redirs = redirs->next;
	}
	
}

void	show_smp_cmd(void *cmd_ptr)
{
	t_smp_cmd	*cmd;
	size_t		a;

	cmd = (t_smp_cmd *) cmd_ptr;
	a = 0;
	while (a < cmd->arg_count)
	{
		printf("\targ:%s at %p\n", cmd->args[a], cmd->args[a]);
		a++;
	}
	printf("\targc:%zu\n", cmd->arg_count);
	print_redirs(cmd->redirections);
}

void	show_cmds(t_smp_cmd **commands, size_t cmd_count)
{
	size_t	c;

	c = 0;
	while (c < cmd_count)
	{
		printf("simple Command #%zu:\n cmd:%s (is_builtin=%d)\n", c + 1, commands[c]->cmd, commands[c]->is_builtin);
		show_smp_cmd(commands[c]);
		c++;
	}
}

void	show_cmd_line(t_cmd_line *cmd_line)
{
	printf("cmdline:\n in:%s out:%s, cmd_count:%zu, pipe_count:%zu\n", cmd_line->infile, cmd_line->outfile, cmd_line->cmd_count, cmd_line->pipe_count);
	printf(" append:%d, heredoc_delimiter:%s\n", cmd_line->append, cmd_line->heredoc_delimiter);
	show_cmds(cmd_line->smp_cmds, cmd_line->cmd_count);
}

// debug
void	print_text_chunks(t_list *chunks)
{
	size_t			size;
	char			*buffer;
	t_text_chunk	*chunk;
	size_t			i;

	i = 0;
	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		size = chunk->len + 1;
		buffer = ft_calloc(size, sizeof (char));
		ft_strlcpy(buffer, chunk->str, size);
		printf("text_chunk[%zu]:%s, len:%zu, expand:%d|\n", i, buffer, chunk->len, chunk->expand);
		chunks = chunks->next;
		free(buffer);
		i++;
	}
}

void	print_path_arr(char **paths)
{
	printf("paths\n");
	while (paths && *paths)
	{
		printf("%s|\n", *paths);
		paths++;
	}
}

