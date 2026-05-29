# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/05/29 10:33:21 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_PATH = inc
SRC_PATH = src
UTILS_PATH = src/utils
PROMPT_PATH = src/prompt

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_PATH)
LIBS = -lreadline

SRCS = $(addprefix $(SRC_PATH)/,       \
		main.c)                        \
		$(addprefix $(UTILS_PATH)/,    \
		string_builder.c               \
		ft_memcpy.c                    \
		ft_strncmp.c                   \
		ft_strcmp.c                    \
		ft_strrchr.c                   \
		ft_strlcpy.c                   \
		ft_strlcat.c                   \
		ft_strlen.c)                   \
		$(addprefix $(PROMPT_PATH)/,   \
		prompt_utils.c                 \
		prompt_git.c                   \
		prompt.c                       \
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