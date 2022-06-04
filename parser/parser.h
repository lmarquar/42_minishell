/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:20:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/03 16:10:49 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h> // perror

# include "../libft/libft.h"
# include "../env/env.h"
# include "../bonus/bonus.h"

enum e_redirection_type
{
	INPUT = 1,
	HEREDOC,
	OUTPUT,
	APPEND
};

typedef struct s_redirection
{
	int		type;
	char	*name;
}	t_redir;

typedef struct s_smp_cmd
{
	char	*cmd;
	char	**args;
	size_t	arg_count;
	int		is_builtin;
	t_list	*redirections;
	size_t	redir_count;
	char	**heredoc_delims;
	size_t	heredoc_count;
}	t_smp_cmd;

typedef struct s_cmd_line
{
	char		*infile;
	char		*outfile;
	size_t		pipe_count;
	size_t		cmd_count;
	t_smp_cmd	**smp_cmds;
	t_smp_cmd	**smp_cmds_start;
	int			append;
	char		*heredoc_delimiter;
}	t_cmd_line;

typedef struct s_bin
{
	char		*in;
	t_cmd_line	*cmd_line;
	t_env_var	*env;
	char		**env_arr;
	int			exit_code;
	char		*cwd;
	char		**paths;
	int			*pid;
}	t_bin;

// interal use

typedef struct s_text_chunk
{
	char	*str;
	size_t	len;
	int		expand;
}	t_text_chunk;

typedef struct s_cmds
{
	t_list		*cmd_lst;
	t_smp_cmd	*current_cmd;
}	t_cmds;

enum e_QUOTE
{
	NO_QUOTE = 0,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

int				parse(const char *input, t_cmd_line *cmd_line, t_env_var *env,
					t_bin *bin);

void			interpret_quotes(char **str, t_env_var *env, int exit_code, int expand);

//parse2

int				handle_unclosed_quotes(t_bin *bin);
int				init_cmds(t_cmds *cmds);

// special character

int				is_space(char c);
int				is_ctrlchr(char c);
int				is_metachr(char c);
int				is_quote(char c);
int				is_dollarchr(char c);

// quote

int				change_quote_state(int state, char c);
int				has_unclosed_quotes(const char *s);
int				contains_unquoted_ctrlchr(const char *s);

// smp_cmd

t_smp_cmd		*new_smp_cmd(
					char *cmd,
					char **args,
					size_t arg_count,
					int is_builtin);
void			add_arg(t_smp_cmd **old, char *arg);
void			clear_smp_cmd(t_smp_cmd *cmd_ptr);

// cmd_line

void			init_cmd_line(t_cmd_line *cmd);
void			assign_token(char **member, char *token);
void			clear_cmd_line(t_cmd_line *cmd);

// chunk

t_text_chunk	*new_chunk(char *str, int expand);
void			split_into_chunks(
					t_list **chunks,
					t_text_chunk **chunk,
					int *state,
					char *s);
size_t			sum_len(t_list *chunks);
char			*join_chunks(t_list *chunks);
void			clear_chunk(void *chk_ptr);

// token

char			*next_token(const char *s, int reset);

// replace

void			expand_env_var(t_text_chunk *chunk, t_env_var *env_vars);
int				replace_question_mark(t_text_chunk *chunk, int exit_code);
void			expansion(t_list *chunks, t_env_var *env, int exit_code);

// array

char			**create_path_arr(char	*path);
char			**create_env_arr(t_env_var *env);
t_smp_cmd		**create_cmd_arr(t_list *cmd_lst);
void			clear_pointer_arr(char ***arr);

// handle_operators

int				handle_redirection(t_smp_cmd *cmd, char *token, int type);
t_redir			*new_redir(char *name, int type);
void			clear_redir(void *redir);
void			expand_redirections(t_list *smp_cmds, t_env_var *env, int exit_code);

//builtins
int				is_builtin(const char *s);

//parse_bonus
int				expand_wildcard_bonus(t_cmds *cmds, char *token);

//debug
void	show_cmd_line(t_cmd_line *cmd_line);

#endif
