# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/06/06 20:55:00 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_PATH = inc
SRC_PATH = src
UTILS_PATH = src/utils
PROMPT_PATH = src/prompt
LEXER_PATH = src/lexer
PARSER_PATH = src/parser
ERROR_PATH = src/error_handler
CLEANUP_PATH = src/clear_resources

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_PATH) -g3
LIBS = -lreadline

SRCS = $(addprefix $(SRC_PATH)/,       \
		debug.c                             \
		init.c                         \
		shell_core.c                   \
		main.c)                        \
		$(addprefix $(CLEANUP_PATH)/,  \
		clear_pipeline.c               \
		clear_resources.c)             \
		$(addprefix $(UTILS_PATH)/,    \
		string_builder.c               \
		ft_realloc.c                   \
		ft_memcpy.c                    \
		ft_strncmp.c                   \
		ft_strcmp.c                    \
		ft_strrchr.c                   \
		ft_strlcpy.c                   \
		ft_strlcat.c                   \
		ft_strlen.c                    \
		ft_strdup.c                    \
		ft_isspace.c)                  \
		$(addprefix $(PROMPT_PATH)/,   \
		prompt_git.c                   \
		prompt.c)                      \
		$(addprefix $(LEXER_PATH)/,    \
		lexer_utils.c                  \
		lexer.c)                       \
		$(addprefix $(PARSER_PATH)/,   \
		heredoc.c                      \
		parser_utils.c                 \
		parser.c)                      \
		$(addprefix $(ERROR_PATH)/,    \
		error_handler.c                \
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