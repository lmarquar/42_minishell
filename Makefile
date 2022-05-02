# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 12:03:48 by chelmerd          #+#    #+#              #
#    Updated: 2022/05/02 16:02:16 by chelmerd         ###   ########.fr        #
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
endif

LIBFT = libft/libft.a

INCLUDES = -I$(READLINE_INCLUDE)


PARSER			= parse.c special_character.c
SRCS_PARSER		= $(addprefix parser/, $(PARSER))
SRCS_MANDATORY	= minishell.c execute.c $(SRCS_PARSER)
OBJS_MANDATORY	= $(patsubst %.c, %.o, $(SRCS_MANDATORY))

all: $(NAME)

$(NAME): $(SRCS_MANDATORY) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -Iparser/ -lreadline #-L$(READLINE_PATH)

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
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean
	make all

.PHONY: all clean fclean re show debug
