/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:08:53 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/25 13:20:48 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_cmds(t_cmds *cmds)
{
	cmds->cmd_lst = NULL;
	cmds->current_cmd = new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
	return (0);
}

int	handle_unclosed_quotes(t_bin *bin)
{
	bin->exit_code = 2;
	return (ft_error(2, "Unclosed quotes!"));
}
