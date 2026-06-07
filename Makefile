# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/06/07 16:28:52 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_PATH = inc
SRC_PATH = src
UTILS_PATH = $(SRC_PATH)/utils
PROMPT_PATH = $(SRC_PATH)/prompt
LEXER_PATH = $(SRC_PATH)/lexer
PARSER_PATH = $(SRC_PATH)/parser
EXECUTOR_PATH = $(SRC_PATH)/executor
ERROR_PATH = $(SRC_PATH)/error
SB_PATH = $(SRC_PATH)/string_builder
CLEANUP_PATH = $(SRC_PATH)/clear_resources

PRINTF_PATH = ./ft_printf
PRINTF_LIB = $(PRINTF_PATH)/libftprintf.a
PRINTF_INC_PATH = ./ft_printf/inc

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_PATH) -I $(PRINTF_INC_PATH) -g3
LIBS = -lreadline

SRCS = $(addprefix $(SRC_PATH)/,       \
		debug.c                             \
		init.c                         \
		shell_core.c                   \
		main.c)                        \
		$(addprefix $(SB_PATH)/,       \
		sb_utils.c                     \
		sb.c)                          \
		$(addprefix $(CLEANUP_PATH)/,  \
		clear_pipeline.c               \
		clear_resources.c)             \
		$(addprefix $(UTILS_PATH)/,    \
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
		parser_utils.c                 \
		parser.c)                      \
		$(addprefix $(EXECUTOR_PATH)/, \
		heredoc.c)                     \
		$(addprefix $(ERROR_PATH)/,    \
		warning.c                      \
		error.c                        \
		)

OBJS = $(SRCS:.c=.o)
	
all: $(NAME)

$(NAME): $(PRINTF_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF_LIB) $(LIBS) -o $(NAME)

$(PRINTF_LIB):
	@make -C $(PRINTF_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(PRINTF_PATH)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(PRINTF_PATH)
	rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all