#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"

int	execute(t_bin *bin);
int	exec_with_pipes(t_bin *bin, int *pid, int fd[]);
int	heredoc_handler(t_cmd_line *cmd_line, int fdout);
int	append(int fdin, int fdout);
int	exec_el(char **arg, t_bin *bin, int fdin, int fdout);

int	exec_builtin(t_bin *bin, char **args, int fdout);
int	exec_cd(char *dir);
int	exec_export(int fdout, t_bin *bin, char *var_ass);
int	exec_echo(int fdout, char **args);
int	handle_dup2error(void);

#endif
