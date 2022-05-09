/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/09 11:23:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* the quote state will be hold until a matching quote is encountered.
*/
int	change_quote_state(int state, char c)
{
	if (!(c == '\'' || c == '"'))
		return (0);
	if (state == -1)
		return (is_quote(c) + 1);
	if (state == NO_QUOTE && c == '\'')
		return (SINGLE_QUOTE);
	if (state == NO_QUOTE && c == '"')
		return (DOUBLE_QUOTE);
	if (state == SINGLE_QUOTE && c == '\'')
		return (-SINGLE_QUOTE);
	if (state == DOUBLE_QUOTE && c == '"')
		return (-DOUBLE_QUOTE);
	return (0);
}

void	add_arg(t_smp_cmd **old, char *arg)
{
	t_smp_cmd	*new;
	char		**new_args;
	size_t		i;

	new_args = ft_calloc((*old)->arg_count + 2, sizeof (char *));
	i = 0;
	while (i < (*old)->arg_count)
	{
		new_args[i] = (*old)->args[i];
		i++;
	}
	new_args[i] = arg;
	new = new_smp_cmd((*old)->cmd, new_args, (*old)->arg_count + 1);
	free(*old);
	*old = new;
}

void	expansion(t_list *chunks, t_env_var *env)
{
	t_text_chunk	*chunk;

	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		if (chunk->expand)
		{
			if (chunk->len == 1)
				chunk->expand = 0;
			else
				expand_env_var(chunk, env);
		}
		chunks = chunks->next;
	}
}

void	interpret_quotes(char **str, t_env_var *env)
{
	char			*result;
	int				quote_state;
	size_t			i;
	t_list			*text_chunks;
	t_text_chunk	*text_chunk;

	text_chunk = NULL;
	text_chunks = NULL;
	i = 0;
	quote_state = -1;
	while ((*str)[i])
	{
		split_into_chunks(&text_chunks, &text_chunk, &quote_state, &(*str)[i]);
		i++;
	}
	if (text_chunk)
		ft_lstadd_back(&text_chunks, ft_lstnew(text_chunk));
	(void) env;
	print_text_chunks(text_chunks);
	expansion(text_chunks, env);
	result = join_chunks(text_chunks);
	//clear text_chunks
	ft_lstclear(&text_chunks, &clear_chunk);
	free(*str);
	*str = result;
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env)
{
	int			error;
	char		*token;
	t_smp_cmd	*smp_cmd;
	t_list		*cmds;

	error = 0;
	token = next_token(input, 1);
	smp_cmd = new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0);
	init_cmd_line(cmd_line);
	cmds = NULL;
	while (token)
	{
		printf("token:%s\n", token);
		if (is_ctrlchr(token[0]))
		{
			if (ft_strncmp("<", token, 2) == 0)
				cmd_line->infile = next_token(input, 0);
			else if (ft_strncmp("<<", token, 3) == 0)
				cmd_line->heredoc_delimiter = next_token(input, 0);
			else if (token[0] == '>')
			{
				cmd_line->outfile = next_token(input, 0);
				if (token[1] == '>')
					cmd_line->append = 1;
			}
			else if (ft_strncmp("|", token, 2) == 0)
			{
				ft_lstadd_back(&cmds, ft_lstnew(smp_cmd));
				smp_cmd = new_smp_cmd(NULL, ft_calloc(1, sizeof (char *)), 0);
				cmd_line->pipe_count++;
				cmd_line->cmd_count++;
			}
			else
			{
				printf("Control charater ('%s') not regonized.\n", token);
				error = 1;
				free(token);
			}
		}
		else
		{
			interpret_quotes(&token, env);
			// expand_env_vars(&token, env);
			if (!smp_cmd->cmd)
				smp_cmd->cmd = token;
			add_arg(&smp_cmd, token);
		}
		token = next_token(input, 0);
	}
	ft_lstadd_back(&cmds, ft_lstnew(smp_cmd));
	cmd_line->simple_commands = create_cmd_arr(cmds);
	ft_lstclear(&cmds, NULL);
	show_cmd_line(cmd_line); // debug
	return (error);
}
