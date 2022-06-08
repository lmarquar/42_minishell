/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:07:56 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/08 16:07:57 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	print_redirs(t_list *redirs)
{
	t_redir	*r;
	char	*redir_type;

	if (!redirs)
		printf("No redirections\n");
	while (redirs)
	{
		r = (t_redir *) redirs->content;
		if (r->type == INPUT)
			redir_type = "INPUT";
		else if (r->type == HEREDOC)
			redir_type = "HEREDOC";
		else if (r->type == OUTPUT)
			redir_type = "OUTPUT";
		else if (r->type == APPEND)
			redir_type = "APPEND";
		else
			redir_type = "UNKOWN";
		printf("type=%s, name=%s\n", redir_type, r->name);
		redirs = redirs->next;
	}
}

static
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
	printf("\theredoc_delims:\n");
	a = 0;
	while (a < cmd->heredoc_count)
	{
		printf("\t\t%s\n", cmd->heredoc_delims[a++]);
	}
	print_redirs(cmd->redirections);
}

static
void	show_cmds(t_smp_cmd **commands, size_t cmd_count)
{
	size_t	c;

	c = 0;
	while (c < cmd_count)
	{
		printf("simple Command #%zu:\n cmd:%s (is_builtin=%d)\n",
			c + 1, commands[c]->cmd, commands[c]->is_builtin);
		show_smp_cmd(commands[c]);
		c++;
	}
}

void	show_cmd_line(t_cmd_line *cmd_line)
{
	printf("cmdline:\ncmd_count:%zu, pipe_count:%zu\n",
		cmd_line->cmd_count, cmd_line->pipe_count);
	show_cmds(cmd_line->smp_cmds, cmd_line->cmd_count);
}

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
		printf("text_chunk[%zu]:%s, len:%zu, expand:%d|\n",
			i, buffer, chunk->len, chunk->expand);
		chunks = chunks->next;
		free(buffer);
		i++;
	}
}
