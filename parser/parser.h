/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:20:00 by chelmerd          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/31 18:14:09 by lmarquar         ###   ########.fr       */
=======
/*   Updated: 2022/06/01 12:45:25 by chelmerd         ###   ########.fr       */
>>>>>>> 2e827740ab600a96aafb6bca24d38731dea0f708
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

typedef struct s_smp_cmd
{
	char	*cmd;
	char	**args;
	size_t	arg_count;
	int		is_builtin;
	char	*infile;
	char	**heredoc;
	int		heredoc_count;
	char	*outfile;
	char	*outfile_append;
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
	char		**heredoc_delimiter;
	char		**files_trunc;
	char		**files_creat;
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

//debug

void			show_smp_cmd(void *cmd_ptr);
void			show_cmd_line(t_cmd_line *cmd_line);
void			print_text_chunks(t_list *chunks);
void			print_path_arr(char **paths);

//builtins
int				is_builtin(const char *s);

//parse_bonus
int				expand_wildcard_bonus(t_cmds *cmds, char *token);

#endif
