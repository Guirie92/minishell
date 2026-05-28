# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/05/28 07:18:21 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_PATH = inc
SRC_PATH = src

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_PATH)
LIBS = -lreadline

SRCS = $(addprefix $(SRC_PATH)/,       \
		main.c                         \
		)

OBJS = $(SRCS:.c=.o)
	
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all