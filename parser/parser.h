/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:20:00 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/02 15:54:48 by chelmerd         ###   ########.fr       */
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
}	t_smp_cmd;

typedef struct s_cmd_line
{
	char		*infile;
	char		*outfile;
	size_t		pipe_count;
	t_smp_cmd	**simple_commands;
	int			append;
	int			heredoc;
}	t_cmd_line;

int	is_space(char c);
int	is_ctrlchr(char c);
int	is_metachr(char c);

int	parse(const char *input, t_cmd_line *cmd_line);

#endif