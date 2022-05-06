/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:44:32 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 15:12:57 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_cmd_line(t_cmd_line *cmd)
{
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_count = 1;
	cmd->pipe_count = 0;
	cmd->simple_commands = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->append = 0;
}

t_smp_cmd	*new_smp_cmd(char *cmd, char **args, size_t arg_count)
{
	t_smp_cmd	*new;

	new = malloc(sizeof (t_smp_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->args = args;
	new->arg_count = arg_count;
	return (new);
}

//TODO: use it
void	clear_smp_cmd(void *cmd_ptr)
{
	t_smp_cmd	*cmd;
	size_t		i;

	cmd = (t_smp_cmd *) cmd_ptr;
	if (cmd->cmd)
		free(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}
