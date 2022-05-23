/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/22 20:12:34 by leon             ###   ########.fr       */
=======
/*   Updated: 2022/05/23 13:12:26 by chelmerd         ###   ########.fr       */
>>>>>>> 87b176a7b83ca09397c2b0290a26b5adfa74cc07
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	interpret_quotes(char **str, t_env_var *env, int exit_code)
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
	print_text_chunks(text_chunks); // debug
	expansion(text_chunks, env, exit_code);
	result = join_chunks(text_chunks);
	ft_lstclear(&text_chunks, &clear_chunk);
	free(*str);
	*str = result;
}

int	parse_operator(const char *input, char *token, t_cmds *cmds,
					t_cmd_line *cmd_line)
{
	if (ft_strncmp("<", token, 2) == 0)
		assign_token(&cmd_line->infile, next_token(input, 0));
	else if (ft_strncmp("<<", token, 3) == 0)
		assign_token(&cmd_line->heredoc_delimiter, next_token(input, 0));
	else if (token[0] == '>')
	{
		assign_token(&cmd_line->outfile, next_token(input, 0));
		cmd_line->append = 0;
		if (token[1] == '>')
			cmd_line->append = 1;
	}
	else if (ft_strncmp("|", token, 2) == 0)
	{
		ft_lstadd_back(&cmds->cmd_lst, ft_lstnew(cmds->current_cmd));
		cmds->current_cmd
			= new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
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

int	parse_word(char *token, t_env_var *env, int exit_code, t_cmds *cmds)
{
	interpret_quotes(&token, env, exit_code);
	if (!cmds->current_cmd->cmd)
	{
		cmds->current_cmd->cmd = token;
		cmds->current_cmd->is_builtin = is_builtin(token);
	}
	add_arg(&cmds->current_cmd, token);
	return (0); //TODO: what could be an error here?
}

static
void	package_info(t_cmd_line *cmd_line, t_env_var *env, t_bin *bin)
{
	cmd_line->smp_cmds_start = cmd_line->smp_cmds;
	bin->cmd_line = cmd_line;
	bin->env = env; // really need to do it here?
	if (bin->env_arr)
	{
		clear_pointer_arr((void **) bin->env_arr);
	}
	bin->env_arr = create_env_arr(env);
	if (!bin->cwd)
		bin->cwd = getcwd(NULL, 0);
	bin->paths = create_path_arr(find_in_env("PATH", 4, env));
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env, t_bin *bin)
{
	int		error;
	char	*token;
	t_cmds	cmds;

	error = 0;
	if (has_unclosed_quotes(input))
	{
		bin->exit_code = 2;
		return (ft_error(2, "Unclosed quotes!"));
	}
	token = next_token(input, 1);
	init_cmd_line(cmd_line);
	cmds.cmd_lst = NULL;
	cmds.current_cmd = new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
	while (token && !error)
	{
		printf("token:%s\n", token);
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
	cmd_line->smp_cmds = create_cmd_arr(cmds.cmd_lst);
	ft_lstclear(&cmds.cmd_lst, NULL);
	show_cmd_line(cmd_line); // debug
	package_info(cmd_line, env, bin);
	return (error);
}
