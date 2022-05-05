# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 12:03:48 by chelmerd          #+#    #+#              #
#    Updated: 2022/04/28 16:58:59 by leon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell
HEADER = minishell.h

READLINE_PATH = /usr/local/opt/readline/lib
READLINE_INCLUDE = /usr/local/opt/readline/include

INCLUDES = $(READLINE_INCLUDE)

SRCS_MANDATORY	= minishell.c
OBJS_MANDATORY	= $(patsubst %.c, %.o, $(SRCS_MANDATORY))

# LIBS = pipex/pipex.a

all: $(NAME)

$(NAME): $(OBJS_MANDATORY) $(LIBS)
	$(CC) $(LFLAGS) $^ -o $@ -lreadline libft_pro.a 

# $(LIBS):
# 	make -C pipex/

debug: CFLAGS := $(CFLAGS) -g
debug: all

$(OBJS_MANDATORY): $(SRCS_MANDATORY)
	$(CC) $(CFLAGS) -c $< -I$(INCLUDES) -o $@

show:
	@echo $(SRCS_MANDATORY)
	@echo $(OBJS_MANDATORY)

clean:
	rm -f $(OBJS_MANDATORY)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re show debug
