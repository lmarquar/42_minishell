/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:41:37 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/18 10:01:59 by chelmerd         ###   ########.fr       */
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
	return (new);
}

/*
* appends arg to array of arguments
*/
void	add_arg(t_smp_cmd **old_cmd, char *arg)
{
	t_smp_cmd	*old;
	t_smp_cmd	*new;
	char		**new_args;
	size_t		i;

	if (!old_cmd)
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
	new = new_smp_cmd(old->cmd, new_args, old->arg_count + 1, old->is_builtin);
	free(old->args);
	free(old);
	*old_cmd = new;
}

//TODO: use it
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
	free(cmd);
}
