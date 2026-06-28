# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/28 05:06:50 by guillsan          #+#    #+#              #
#    Updated: 2026/06/28 20:56:05 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
ENV_DIR = $(SRC_DIR)/env
PROMPT_DIR = $(SRC_DIR)/prompt
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXPANDER_DIR = $(SRC_DIR)/expander
EXECUTOR_DIR = $(SRC_DIR)/executor
ERROR_DIR = $(SRC_DIR)/error
SIGNAL_DIR = $(SRC_DIR)/signal
BUILTINS_DIR = $(SRC_DIR)/builtins
SB_DIR = $(SRC_DIR)/string_builder
CLEANUP_DIR = $(SRC_DIR)/clear_resources

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC_DIR = $(LIBFT_DIR)/inc

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -I $(LIBFT_INC_DIR) -g3
LIBS = -lreadline

SRCS = $(addprefix $(SRC_DIR)/,        \
		debug.c                             \
		init.c                         \
		shell_core.c                   \
		main.c)                        \
		$(addprefix $(ENV_DIR)/,       \
		env_alpha.c                    \
		env_funcs.c                    \
		env_utils.c                    \
		env.c)                         \
		$(addprefix $(SB_DIR)/,        \
		sb_utils.c                     \
		sb.c)                          \
		$(addprefix $(CLEANUP_DIR)/,   \
		clear_pipeline.c               \
		clear_resources.c)             \
		$(addprefix $(PROMPT_DIR)/,    \
		prompt_git.c                   \
		prompt.c)                      \
		$(addprefix $(LEXER_DIR)/,     \
		lexer_utils.c                  \
		lexer.c)                       \
		$(addprefix $(PARSER_DIR)/,    \
		parser_hc.c                    \
		parser_utils.c                 \
		parser.c)                      \
		$(addprefix $(EXPANDER_DIR)/,  \
		calc_env_len.c                 \
		exp_env.c                      \
		calc_len_token.c               \
		exp_env_token.c                \
		expander.c)                    \
		$(addprefix $(EXECUTOR_DIR)/,  \
		executor.c                     \
		process_cmd.c                  \
		fork.c                         \
		pipe.c                         \
		redirs.c                       \
		path.c                         \
		hc_utils.c                     \
		heredoc.c)                     \
		$(addprefix $(BUILTINS_DIR)/,  \
		unset.c                        \
		export.c                       \
		cd.c                           \
		exit.c                         \
		echo.c                         \
		env.c                          \
		pwd.c                          \
		builtins.c)                    \
		$(addprefix $(ERROR_DIR)/,     \
		warning.c                      \
		error_exit.c                   \
		error.c)                       \
		$(addprefix $(SIGNAL_DIR)/,    \
		signal.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
	
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all