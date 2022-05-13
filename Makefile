# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 12:03:48 by chelmerd          #+#    #+#              #
#    Updated: 2022/05/13 16:33:56 by leon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
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

PARSER			=	parse.c special_character.c replace.c debug.c \
					chunk.c token.c cmd_line.c quote.c arrays.c
SRCS_PARSER		= $(addprefix parser/, $(PARSER))
BUILTINS		=	builtin_utils.c
SRCS_BUILTINS	= $(addprefix builtins/, $(BUILTINS))
ENV				=	env.c env_list.c
SRCS_ENV		= $(addprefix env/, $(ENV))
EXECUTER		= execute.c execute_funcs.c exec_el.c exec_with_pipes.c exec_builtin.c
SRCS_EXECUTER	= $(addprefix executer/, $(EXECUTER))
SRCS_MANDATORY	= minishell.c $(SRCS_PARSER) $(SRCS_EXECUTER) $(SRCS_BUILTINS) $(SRCS_ENV)
OBJS_MANDATORY	= $(patsubst %.c, %.o, $(SRCS_MANDATORY))

all: $(NAME)

$(NAME): $(SRCS_MANDATORY) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDES) -lreadline $(RL_LIBARY)

# $(LIBS):
# 	make -C pipex/

debug: CFLAGS := $(CFLAGS) -g
debug: all

$(OBJS_MANDATORY): $(SRCS_MANDATORY)
	$(CC) $(CFLAGS) -c $^ -Iparser/

$(LIBFT):
	make -C libft

show:
	@echo $(SRCS_MANDATORY)
	@echo $(OBJS_MANDATORY)

clean:
	rm -f $(OBJS_MANDATORY)
	rm -rfd minishell.dSYM
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean
	make all

.PHONY: all clean fclean re show debug
