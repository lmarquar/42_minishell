/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:20:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 11:34:21 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define NO_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

typedef struct s_smp_cmd
{
	char	*cmd;
	char	**args;
	size_t	arg_count;
}	t_smp_cmd;

typedef struct s_cmd_line
{
	char		*infile;
	char		*outfile;
	size_t		pipe_count;
	size_t		cmd_count;
	t_smp_cmd	**simple_commands;
	int			append;
	char		*heredoc_delimiter;
}	t_cmd_line;

typedef struct s_env_var
{
	char				*key;
	char				*val;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_text_chunk
{
	char	*str;
	size_t	len;
	int		expand;
} t_text_chunk;

int	is_space(char c);
int	is_ctrlchr(char c);
int	is_metachr(char c);
int	is_quote(char c);

int	parse(const char *input, t_cmd_line *cmd_line, t_env_var *env);

int	expand_env_vars(char **input, t_env_var *env_vars);
void	expand_env_var(t_text_chunk *chunk, t_env_var *env_vars);

//debug
void	show_cmd_line(t_cmd_line *cmd_line);

#endif
