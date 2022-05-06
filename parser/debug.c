/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:21:44 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 15:08:56 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_cmds(t_smp_cmd **commands, size_t cmd_count)
{
	size_t	c;
	size_t	a;

	c = 0;
	while (c < cmd_count)
	{
		printf("simple Command:\n cmd:%s\n", commands[c]->cmd);
		a = 0;
		while (a < commands[c]->arg_count)
		{
			printf("\targ:%s at %p\n", commands[c]->args[a], commands[c]->args[a]);
			a++;
		}
		printf("\targc:%zu\n", commands[c]->arg_count);
		c++;
	}
}

void	show_cmd_line(t_cmd_line *cmd_line)
{
	printf("cmdline:\n in:%s out:%s, cmd_count:%zu, pipe_count:%zu\n", cmd_line->infile, cmd_line->outfile, cmd_line->cmd_count, cmd_line->pipe_count);
	printf(" append:%d, heredoc_delimiter:%s\n", cmd_line->append, cmd_line->heredoc_delimiter);
	show_cmds(cmd_line->simple_commands, cmd_line->cmd_count);
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
		i++;
	}
}
