/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:44:32 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/06 12:57:58 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_cmd_line(t_cmd_line *cmd)
{
	cmd->cmd_count = 1;
	cmd->pipe_count = 0;
	cmd->smp_cmds = NULL;
	cmd->smp_cmds_start = NULL;
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
	while (cmd->smp_cmds_start && cmd->smp_cmds_start[i])
	{
		clear_smp_cmd(cmd->smp_cmds_start[i]);
		i++;
	}
	free(cmd->smp_cmds_start);
}
