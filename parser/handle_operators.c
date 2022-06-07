/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:12 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 14:56:52 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static
int	check_token(char *token)
{
	if (!token)
		return (ft_error(2, "syntax error: no token"));
	if (*token == '\0')
	{
		free(token);
		return (ft_error(2, "syntax error: empty token"));
	}
	if (contains_unquoted_ctrlchr(token))
	{
		free(token);
		return (ft_error(2, "syntax error: unexpected token"));
	}
	return (0);
}

t_redir	*new_redir(char *name, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->name = name;
	redir->type = type;
	return (redir);
}

void	clear_redir(void *redir)
{
	t_redir	*r;

	if (!redir)
		return ;
	r = (t_redir *) redir;
	if (r->name)
		free(r->name);
	free(r);
}

int	handle_redirection(t_smp_cmd *cmd, char *token, int type)
{
	t_redir	*redir;

	if (check_token(token) != 0)
		return (2);
	redir = new_redir(token, type);
	ft_lstadd_back(&cmd->redirections, ft_lstnew(redir));
	if (type == HEREDOC)
	{
		cmd->heredoc_count++;
	}
	return (0);
}

void	expand_redirections(t_list *smp_cmds, t_env_var *env, int exit_code)
{
	t_smp_cmd	*cmd;
	t_list		*redirs;
	t_redir		*r;
	size_t		i;

	while (smp_cmds)
	{
		cmd = (t_smp_cmd *) smp_cmds->content;
		redirs = cmd->redirections;
		if (cmd->heredoc_count)
			cmd->heredoc_delims
				= ft_calloc(cmd->heredoc_count + 1, sizeof(char *));
		i = 0;
		while (redirs)
		{
			r = (t_redir *) redirs->content;
			interpret_quotes(&r->name, env, exit_code, (r->type != HEREDOC));
			if (r->type == HEREDOC)
				cmd->heredoc_delims[i++] = ft_strdup(r->name);
			redirs = redirs->next;
		}
		smp_cmds = smp_cmds->next;
	}
}
