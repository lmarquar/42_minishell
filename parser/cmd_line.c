/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:44:32 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/25 16:31:19 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_cmd_line(t_cmd_line *cmd)
{
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_count = 1;
	cmd->pipe_count = 0;
	cmd->smp_cmds = NULL;
	cmd->smp_cmds_start = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->append = 0;
}

void	assign_token(char **member, char *token)
{
	if (*member)
		free(*member);
	*member = token;
}

void	clear_cmd_line(t_cmd_line *cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	i = 0;
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	i = 0;
	while (cmd->smp_cmds_start && cmd->smp_cmds_start[i])
	{
		clear_smp_cmd(cmd->smp_cmds_start[i]);
		i++;
	}
	free(cmd->smp_cmds_start);
}
