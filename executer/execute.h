#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../parser/parser.h"
# include "../libft/libft.h"

int	execute(t_cmd_line *cmd_line, t_env_var *env_vars);
int	heredoc_handler(t_cmd_line *cmd_line, int fdout);
int append(int fdin, int fdout);
int	exec_el(char **arg, char **paths, int fdin, int fdout);

#endif
