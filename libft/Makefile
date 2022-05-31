# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 09:33:08 by chelmerd          #+#    #+#              #
#    Updated: 2022/02/24 13:44:30 by chelmerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
HEADERS = libft.h
SRCS_MANDATORY	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
				ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
				ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c
SRCS_BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c
SRCS_EXTRA		= ft_error.c ft_printf.c

OBJS_MANDATORY	= $(patsubst %.c, %.o, $(SRCS_MANDATORY))
OBJS_BONUS		= $(patsubst %.c, %.o, $(SRCS_BONUS))
OBJS_EXTRA		= $(patsubst %.c, %.o, $(SRCS_EXTRA))

$(NAME): $(OBJS_MANDATORY) $(OBJS_BONUS) $(OBJS_EXTRA)
	ar -cr $(NAME) $(OBJS_MANDATORY)
	ar -cr $(NAME) $(OBJS_BONUS)
	ar -cr $(NAME) $(OBJS_EXTRA)

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS_MANDATORY)
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS_EXTRA)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
