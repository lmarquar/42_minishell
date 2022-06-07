/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 15:21:19 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	interpret_quotes(char **str, t_env_var *env, int exit_code, int expand)
{
	char			*result;
	int				quote_state;
	size_t			i;
	t_list			*text_chunks;
	t_text_chunk	*text_chunk;

	if (!*str)
		return ;
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
	if (expand)
		expansion(text_chunks, env, exit_code);
	result = join_chunks(text_chunks);
	ft_lstclear(&text_chunks, &clear_chunk);
	free(*str);
	*str = result;
}

static
int	parse_word(char *token, t_env_var *env, int exit_code, t_cmds *cmds)
{
	if (ft_strchr(token, '*') && !ft_strchr(token, '\'') && \
		!ft_strchr(token, '\"') && !ft_strchr(token, '$'))
	{
		if (!expand_wildcard_bonus(cmds, token))
		{
			free(token);
			token = NULL;
		}
	}
	if (token)
	{
		interpret_quotes(&token, env, exit_code, 1);
		if (!cmds->current_cmd->cmd)
		{
			cmds->current_cmd->cmd = token;
			cmds->current_cmd->is_builtin = is_builtin(token);
		}
		add_arg(&cmds->current_cmd, token);
	}
	return (0);
}

static
int	parse_operator(const char *input, char *token, t_cmds *cmds,
					t_cmd_line *cmd_line)
{
	t_smp_cmd	*current;

	current = cmds->current_cmd;
	if (ft_strncmp("<", token, 2) == 0)
		return (handle_redirection(current, next_token(input, 0), INPUT));
	else if (ft_strncmp("<<", token, 3) == 0)
		return (handle_redirection(current, next_token(input, 0), HEREDOC));
	else if (ft_strncmp(">", token, 2) == 0)
		return (handle_redirection(current, next_token(input, 0), OUTPUT));
	else if (ft_strncmp(">>", token, 3) == 0)
		return (handle_redirection(current, next_token(input, 0), APPEND));
	else if (ft_strncmp("|", token, 2) == 0)
	{
		ft_lstadd_back(&cmds->cmd_lst, ft_lstnew(current));
		current = new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
		cmd_line->pipe_count++;
		cmd_line->cmd_count++;
	}
	else
	{
		printf("Control operator ('%s') not supported.\n", token);
		return (1);
	}
	return (0);
}

static
int	package_info(t_cmd_line *cmd_line, t_bin *bin, int error)
{
	if (error)
		return (error);
	show_cmd_line(cmd_line);
	cmd_line->smp_cmds_start = cmd_line->smp_cmds;
	if (cmd_line->cmd_count > 1
		&& !cmd_line->smp_cmds[cmd_line->cmd_count - 1]->cmd)
	{
		bin->exit_code = 2;
		return (ft_error(2, "unexpected token at the end"));
	}
	bin->cmd_line = cmd_line;
	if (bin->env_arr)
	{
		clear_pointer_arr(&bin->env_arr);
	}
	bin->env_arr = create_env_arr(bin->env);
	if (!bin->cwd)
		bin->cwd = getcwd(NULL, 0);
	bin->paths = create_path_arr(find_in_env("PATH", 4, bin->env));
	return (0);
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env, t_bin *bin)
{
	int		error;
	char	*token;
	t_cmds	cmds;

	if (has_unclosed_quotes(input))
		return (handle_unclosed_quotes(bin));
	token = next_token(input, 1);
	init_cmds(&cmds);
	error = 0;
	while (token && !error)
	{
		if (is_ctrlchr(token[0]))
		{
			error = parse_operator(input, token, &cmds, cmd_line);
			free(token);
		}
		else
			parse_word(token, env, bin->exit_code, &cmds);
		token = next_token(input, 0);
	}
	ft_lstadd_back(&cmds.cmd_lst, ft_lstnew(cmds.current_cmd));
	expand_redirections(cmds.cmd_lst, env, bin->exit_code);
	cmd_line->smp_cmds = create_cmd_arr(cmds.cmd_lst);
	ft_lstclear(&cmds.cmd_lst, NULL);
	return (package_info(cmd_line, bin, error));
}
