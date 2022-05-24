#ifndef BONUS_H
# define BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

char	**replace_ast_bonus(char *s);
char	**ft_split_pattern(char *s, char c, char *pat);

#endif