/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:56:37 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/08 16:07:10 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include "../libmin/libmin.h"

void	close_ifn_inout(int fd);
int		handle_dup2error(void);
int		get_out_fd(t_list *redirs, int fd);

int		exec_builtin(t_bin *bin, char **args, int fdout);
int		exec_el(char **arg, t_bin *bin, int fdin, int fdout);

int		heredoc_handler(t_bin *bin, char *delim);
int		dumb_heredoc_handler(t_bin *bin, char *delim);
int		heredoc_controller(t_bin *bin, t_list *redirs, char *name, int fd);
int		contains_hdoc_or_in(t_list *redir);
int		get_in_fd(t_bin *bin, t_list *redirs, int fd);

size_t	decr_int_incr_ptr(size_t *i, void ***ptr);
int		exec_with_pipes(t_bin *bin, int *pid);

void	ignore_signals(void);
int		execute(t_bin *bin);
#endif
