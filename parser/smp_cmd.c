/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:41:37 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/06 12:15:05 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* allocates and initalize a simple command with the given parameters
*/
t_smp_cmd	*new_smp_cmd(
	char *cmd,
	char **args,
	size_t arg_count,
	int is_builtin)
{
	t_smp_cmd	*new;

	new = malloc(sizeof (t_smp_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->args = args;
	new->arg_count = arg_count;
	new->is_builtin = is_builtin;
	new->redirections = NULL;
	new->redir_count = 0;
	new->heredoc_delims = NULL;
	new->heredoc_count = 0;
	return (new);
}

/*
* appends arg to array of arguments
*/
void	add_arg(t_smp_cmd **old_cmd, char *arg)
{
	t_smp_cmd	*old;
	char		**new_args;
	size_t		i;

	if (!old_cmd || !arg)
		return ;
	old = *old_cmd;
	new_args = ft_calloc(old->arg_count + 2, sizeof (char *));
	i = 0;
	while (i < old->arg_count && old && old->args[i])
	{
		new_args[i] = old->args[i];
		i++;
	}
	new_args[i] = arg;
	free(old->args);
	old->args = new_args;
	old->arg_count += 1;
}

void	clear_smp_cmd(t_smp_cmd *cmd_ptr)
{
	t_smp_cmd	*cmd;
	size_t		i;

	cmd = (t_smp_cmd *) cmd_ptr;
	if (cmd->cmd)
		free(cmd->cmd);
	i = 1;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	if (cmd->redirections)
		ft_lstclear(&cmd->redirections, &clear_redir);
	if (cmd->heredoc_delims)
		clear_pointer_arr(&cmd->heredoc_delims);
	free(cmd);
}
