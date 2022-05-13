/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:17:17 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/10 13:18:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ft_lstclear(&text_chunks, &free);
	free(*str);
	*str = result;
}

typedef struct s_cmds
{
	t_list		*cmd_lst;
	t_smp_cmd	*current_cmd;
}	t_cmds;

int	parse_operator(const char *input, char *token, t_cmds *cmds,
					t_cmd_line *cmd_line)
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
		ft_lstadd_back(&cmds->cmd_lst, ft_lstnew(cmds->current_cmd));
		cmds->current_cmd
			= new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
		cmd_line->pipe_count++;
		cmd_line->cmd_count++;
	}
	else
	{
		printf("Control charater ('%s') not regonized.\n", token);
		return (1);
	}
	return (0);
}

int	parse_word(char *token, t_env_var *env, t_cmds *cmds)
{
	interpret_quotes(&token, env);
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
	bin->cmd_line = cmd_line;
	bin->env = env; // really need to do it here?
	bin->env_arr = create_env_arr(env);
	bin->cwd = find_in_env("PWD", 3, env);
	bin->paths = create_path_arr(find_in_env("PATH", 4, env), bin->cwd);
}

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env, t_bin *bin)
{
	int		error;
	char	*token;
	t_cmds	cmds;

	error = 0;
	token = next_token(input, 1);
	init_cmd_line(cmd_line);
	cmds.cmd_lst = NULL;
	cmds.current_cmd = new_smp_cmd(NULL, ft_calloc(2, sizeof (char *)), 0, 0);
	while (token && !error)
	{
		printf("token:%s\n", token);
		if (is_ctrlchr(token[0]))
			error = parse_operator(input, token, &cmds, cmd_line);
		else
			parse_word(token, env, &cmds);
		token = next_token(input, 0);
	}
	ft_lstadd_back(&cmds.cmd_lst, ft_lstnew(cmds.current_cmd));
	cmd_line->simple_commands = create_cmd_arr(cmds.cmd_lst);
	ft_lstclear(&cmds.cmd_lst, NULL);
	show_cmd_line(cmd_line); // debug
	package_info(cmd_line, env, bin);
	return (error);
}
