# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 11:01:55 by lmarquar          #+#    #+#              #
#    Updated: 2022/04/28 11:26:23 by chelmerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
LBFTSRC	:= ft_strjoin.c ft_split.c ft_strtrim.c ft_calloc.c
LBFTDIR	:= libft_funcs/
SRC		:= pipex.c pipex_piping.c pipex_universal.c pipex_bonus.c
OBJ		:= $(patsubst %.c, %.o, $(SRC))
LBFTOBJ	:= $(LBFTSRC:.c=.o)
NAME	:= pipex.a


all: $(NAME)

bonus: all

re: clean all

$(NAME): $(OBJ)
	ar -cr $@ $^

$(OBJ): $(SRC) $(LBFTSRC)
	$(CC) $(CFLAGS) -c $(SRC) $(LBFTSRC)

$(LBFTSRC):
	cd $(LBFTDIR) && cp $@ ..

clean:
	rm -f $(OBJ) $(LBFTSRC) $(LBFTOBJ)
	rm -f $(NAME)
	rm -f outfile

fclean: clean
	rm $(LBFTSRC)
