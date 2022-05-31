/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:20:57 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/25 13:33:24 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_wildcard_bonus(t_cmds *cmds, char *token)
{
	char	**arr;
	int		i;

	arr = replace_ast_bonus(token);
	if (!arr)
		return (1);
	if (!cmds->current_cmd->cmd)
	{
		cmds->current_cmd->cmd = arr[0];
		cmds->current_cmd->is_builtin = is_builtin(arr[0]);
	}
	i = 0;
	while (arr[i])
	{
		add_arg(&cmds->current_cmd, arr[i]);
		i++;
	}
	i = 0;
	free(arr);
	return (0);
}
