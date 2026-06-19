# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/06/19 18:37:12 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_PATH = inc
SRC_PATH = src
ENV_PATH = $(SRC_PATH)/env
PROMPT_PATH = $(SRC_PATH)/prompt
LEXER_PATH = $(SRC_PATH)/lexer
PARSER_PATH = $(SRC_PATH)/parser
EXPANDER_PATH = $(SRC_PATH)/expander
EXECUTOR_PATH = $(SRC_PATH)/executor
ERROR_PATH = $(SRC_PATH)/error
SIGNAL_PATH = $(SRC_PATH)/signal
BUILTINS_PATH = $(SRC_PATH)/builtins
SB_PATH = $(SRC_PATH)/string_builder
CLEANUP_PATH = $(SRC_PATH)/clear_resources

LIBFT_PATH = ./libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_INC_PATH = $(LIBFT_PATH)/inc

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_PATH) -I $(LIBFT_INC_PATH) -g3
LIBS = -lreadline

SRCS = $(addprefix $(SRC_PATH)/,       \
		debug.c                             \
		init.c                         \
		shell_core.c                   \
		main.c)                        \
		$(addprefix $(ENV_PATH)/,      \
		env_utils.c                    \
		env.c)                         \
		$(addprefix $(SB_PATH)/,       \
		sb_utils.c                     \
		sb.c)                          \
		$(addprefix $(CLEANUP_PATH)/,  \
		clear_pipeline.c               \
		clear_resources.c)             \
		$(addprefix $(PROMPT_PATH)/,   \
		prompt_git.c                   \
		prompt.c)                      \
		$(addprefix $(LEXER_PATH)/,    \
		lexer_utils.c                  \
		lexer.c)                       \
		$(addprefix $(PARSER_PATH)/,   \
		parser_hc.c                    \
		parser_utils.c                 \
		parser.c)                      \
		$(addprefix $(EXPANDER_PATH)/, \
		calc_env_len.c                 \
		exp_env.c                      \
		calc_len_token.c               \
		exp_env_token.c                \
		expander.c)                    \
		$(addprefix $(EXECUTOR_PATH)/, \
		process_cmd.c                  \
		redirs.c                       \
		path.c                         \
		executor.c                     \
		hc_utils.c                     \
		heredoc.c)                     \
		$(addprefix $(BUILTINS_PATH)/, \
		echo.c                         \
		builtins.c)                    \
		$(addprefix $(ERROR_PATH)/,    \
		warning.c                      \
		error.c)                       \
		$(addprefix $(SIGNAL_PATH)/,   \
		signal.c                       \
		)

OBJS = $(SRCS:.c=.o)
	
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all