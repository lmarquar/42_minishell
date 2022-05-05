/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/04 15:19:06 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* the quote state will be hold until a matching quote is encountered.
*/
int	change_quote_state(int state, char c)
{
	if (!(c == '\'' || c == '"'))
		return (state);
	if (state == NO_QUOTE && c == '\'')
		return (SINGLE_QUOTE);
	if (state == NO_QUOTE && c == '"')
		return (DOUBLE_QUOTE);
	if (state == SINGLE_QUOTE && c == '\'')
		return (NO_QUOTE);
	if (state == DOUBLE_QUOTE && c == '"')
		return (NO_QUOTE);
	return (state);
}

/*
* tokens can be either words or control operators
*/
size_t	next_token_len(const char *s, int quote_state, int unit_is_word)
{
	size_t	token_len;

	token_len = 0;
	quote_state = 0;
	while (s && s[token_len])
	{
		quote_state = change_quote_state(quote_state, s[token_len]);
		if (!unit_is_word)
		{
			if (!is_ctrlchr(s[token_len]))
				break ;
		}
		else if (quote_state == NO_QUOTE && is_metachr(s[token_len]))
			break ;
		token_len++;
	}
	return (token_len);
}

char	*next_token(const char *s, int reset)
{
	static size_t	i = 0;
	char			*token;
	size_t			token_len;
	int				quote_state;

	if (reset)
		i = 0;
	quote_state = change_quote_state(NO_QUOTE, s[i]);
	while (quote_state == NO_QUOTE && s[i] && is_space(s[i]))
		i++;
	if (quote_state == NO_QUOTE && is_ctrlchr(s[i]))
		token_len = next_token_len(&s[i], quote_state, 0);
	else
		token_len = next_token_len(&s[i], quote_state, 1);
	if (token_len == 0)
		return (NULL);
	token = ft_calloc(token_len + 1, sizeof (char));
	ft_strlcpy(token, &s[i], token_len + 1);
	i += token_len;
	return (token);
}

void	init_cmd_line(t_cmd_line *cmd)
{
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_count = 1;
	cmd->pipe_count = 0;
	cmd->simple_commands = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->append = -1;
}

void	init_smp_cmd(t_smp_cmd **smp_c, char *cmd, char **args, size_t arg_count)
{
	t_smp_cmd	*new;

	new = malloc(sizeof (t_smp_cmd));
	new->cmd = cmd;
	new->args = args;
	new->arg_count = arg_count;
	*smp_c = new;
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = malloc(size);
	ft_bzero(new, size);
	ft_memmove(new, ptr, size);

	return (new);
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
	init_smp_cmd(&new, (*old)->cmd, new_args, (*old)->arg_count + 1);
	free(*old);
	*old = new;
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env)
{
	int			error;
	char		*token;
	t_smp_cmd	*smp_cmd;

	error = 0;
	token = next_token(input, 1);
	init_smp_cmd(&smp_cmd, NULL, ft_calloc(2, sizeof (char *)), 0);
	init_cmd_line(cmd_line);
	cmd_line->simple_commands = ft_calloc(3, sizeof (t_smp_cmd));
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
				cmd_line->simple_commands[cmd_line->cmd_count - 1] = smp_cmd;
				init_smp_cmd(&smp_cmd, NULL, ft_calloc(1, sizeof (char *)), 0);
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
			expand_env_vars(&token, env);
			if (!smp_cmd->cmd)
				smp_cmd->cmd = token;
			add_arg(&smp_cmd, token);
		}
		token = next_token(input, 0);
	}
	cmd_line->simple_commands[cmd_line->cmd_count - 1] = smp_cmd;
	show_cmd_line(cmd_line);
	return (error);
}
