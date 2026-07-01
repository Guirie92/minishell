# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 20:50:11 by guillsan          #+#    #+#              #
#    Updated: 2026/07/01 11:39:16 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
EXEC = a.out

SRC_DIR = src
SRC_PF_DIR = src/printf
SRC_PF_UTILS_DIR = src/printf/utils
SRC_PF_FLAGS_DIR = src/printf/utils/flags
INC_DIR = inc
OBJ_DIR = obj

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

SRCS = 	$(addprefix $(SRC_DIR)/,            \
		ft_atoi.c                           \
		ft_abs.c                            \
		ft_bzero.c                          \
		ft_itoa_buffer.c                    \
		ft_isalpha.c                        \
		ft_isalnum.c                        \
		ft_isdigit.c                        \
		ft_realloc.c                        \
		ft_memcpy.c                         \
		ft_strncmp.c                        \
		ft_strcmp.c                         \
		ft_strchr_pos.c                     \
		ft_strchr.c                         \
		ft_strrchr.c                        \
		ft_strlcpy.c                        \
		ft_strlcat.c                        \
		ft_strlen.c                         \
		ft_strdup.c                         \
		ft_strndup.c                        \
		ft_strjoin.c                        \
		ft_count_digits.c                   \
		ft_split.c                          \
		ft_memset.c                         \
		ft_memmove.c                        \
		ft_calloc.c                         \
		ft_str_isspace.c                    \
		ft_isspace.c)                       \
		$(addprefix $(SRC_PF_DIR)/,         \
		ft_char_ptr_handler.c               \
		ft_numeric_handler.c                \
		ft_parse.c                          \
		ft_printf.c)                        \
		$(addprefix $(SRC_PF_UTILS_DIR)/,   \
		ft_printf_init.c                    \
		ft_itoa_print.c                     \
		ft_ui64toa_base_print.c)            \
		$(addprefix $(SRC_PF_FLAGS_DIR)/,   \
		ft_calculate_arglen.c               \
		ft_flag_evaluation.c                \
		ft_flag_utils.c                     \
		ft_flags_handler.c                  \
		ft_invalid_format.c                 \
		ft_valid_format.c) 

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all