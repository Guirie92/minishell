# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 20:50:11 by guillsan          #+#    #+#              #
#    Updated: 2026/06/19 22:12:47 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
EXEC = a.out

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_PATH)

SRC_PATH = src
SRC_PF_PATH = src/printf
SRC_PF_UTILS_PATH = src/printf/utils
SRC_PF_FLAGS_PATH = src/printf/utils/flags
INC_PATH = inc

SRCS = 	$(addprefix $(SRC_PATH)/,           \
		ft_atoi.c                          \
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
		ft_count_digits.c                   \
		ft_split.c                          \
		ft_memmove.c                        \
		ft_calloc.c                         \
		ft_isspace.c)                       \
		$(addprefix $(SRC_PF_PATH)/,        \
		ft_char_ptr_handler.c               \
		ft_numeric_handler.c                \
		ft_parse.c                          \
		ft_printf.c)                        \
		$(addprefix $(SRC_PF_UTILS_PATH)/,  \
		ft_printf_init.c                    \
		ft_itoa_print.c                     \
		ft_ui64toa_base_print.c)            \
		$(addprefix $(SRC_PF_FLAGS_PATH)/,  \
		ft_calculate_arglen.c               \
		ft_flag_evaluation.c                \
		ft_flag_utils.c                     \
		ft_flags_handler.c                  \
		ft_invalid_format.c                 \
		ft_valid_format.c) 

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) *.out

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all