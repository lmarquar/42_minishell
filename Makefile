# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leon <leon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 12:03:48 by chelmerd          #+#    #+#              #
#    Updated: 2022/05/17 12:36:48by lmarquar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell
NAME_LEAKS = minishell_leaks
NAME_BONUS = minishell_bonus
NAME_DEBUG = minishell_debug
HEADER = minishell.h

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)

endif
ifeq ($(UNAME), Darwin)
	READLINE_PATH = /usr/local/opt/readline/lib
	READLINE_INCLUDE = /usr/local/opt/readline/include
	RL_LIBARY = -L$(READLINE_PATH)
endif

LIBFT = libft/libft.a

INCLUDES = -I$(READLINE_INCLUDE) -Iparser -Ibuiltin -Iexecuter

LIBMIN			= universal_funcs.c
SRCS_LIBMIN		= $(addprefix libmin/, $(LIBMIN))
PARSER			=	parse.c parse2.c special_character.c replace.c \
					chunk.c token.c cmd_line.c quote.c arrays.c parse_nobonus.c \
					smp_cmd.c handle_operators.c
SRCS_PARSER		= $(addprefix parser/, $(PARSER))
BUILTINS		=	builtin_utils.c env.c exit.c echo.c export.c pwd.c unset.c cd.c
SRCS_BUILTINS	= $(addprefix builtins/, $(BUILTINS))
ENV				=	env.c env_list.c env_from_str.c
SRCS_ENV		= $(addprefix env/, $(ENV))
EXECUTER		= execute.c exec_funcs.c exec_el.c exec_with_pipes.c exec_builtin.c
SRCS_EXECUTER	= $(addprefix executer/, $(EXECUTER))
BONUS			= ft_split_pattern.c replace_ast_bonus.c
SRCS_BON_FILES	= $(addprefix bonus/, $(BONUS))
SRCS_PARSER_BON	= $(subst nobonus,bonus,$(SRCS_PARSER))
SRCS_MANDATORY	= minishell.c nodebug.c $(SRCS_PARSER) $(SRCS_EXECUTER) $(SRCS_BUILTINS) $(SRCS_ENV) $(SRCS_LIBMIN)
SRCS_BONUS		= minishell.c nodebug.c $(SRCS_PARSER_BON) $(SRCS_EXECUTER) $(SRCS_BUILTINS) $(SRCS_ENV) $(SRCS_LIBMIN) $(SRCS_BON_FILES)
SRCS_DEBUG		= $(subst nodebug,debug,$(SRCS_MANDATORY))


all: mandatory bonus leaks debug

mandatory:
	make SRCS='$(SRCS_MANDATORY)' $(NAME)

bonus:
	make SRCS='$(SRCS_BONUS)' $(NAME_BONUS)

leaks:
	make CFLAGS='$(CFLAGS) -g -fsanitize=address' SRCS='$(SRCS_DEBUG)' $(NAME_LEAKS)

debug:
	make CFLAGS='$(CFLAGS) -g' SRCS='$(SRCS_DEBUG)' $(NAME_DEBUG)

$(NAME) $(NAME_BONUS) $(NAME_LEAKS) $(NAME_DEBUG): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $@ $(INCLUDES) -lreadline $(RL_LIBARY)

$(LIBFT):
	make -C libft

show:
	@echo $(SRCS_MANDATORY)
	@echo $(OBJS_MANDATORY)

clean:
	rm -rfd $(NAME).dSYM
	rm -rfd $(NAME_BONUS).dSYM
	rm -rfd $(NAME_LEAKS).dSYM
	rm -rfd $(NAME_DEBUG).dSYM
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_LEAKS)
	rm -f $(NAME_DEBUG)
	make -C libft fclean

re: fclean
	make all

.PHONY: all clean fclean re show debug bonus mandatory leaks
