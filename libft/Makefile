# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 20:50:11 by guillsan          #+#    #+#              #
#    Updated: 2026/06/09 13:22:09 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
EXEC = a.out

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_PATH)

SRC_PATH = src
SRC_UTILS_PATH = src/utils
SRC_FLAGS_PATH = src/utils/flags
INC_PATH = inc

SRCS = 	$(addprefix $(SRC_PATH)/,        \
		ft_char_ptr_handler.c            \
		ft_numeric_handler.c             \
		ft_parse.c                       \
		ft_printf.c)                     \
		$(addprefix $(SRC_UTILS_PATH)/,  \
		ft_isdigit.c                     \
		ft_printf_init.c                 \
		ft_itoa_print.c                  \
		ft_libft_utils.c                 \
		ft_ui64toa_base_print.c)         \
		$(addprefix $(SRC_FLAGS_PATH)/,  \
		ft_calculate_arglen.c            \
		ft_flag_evaluation.c             \
		ft_flag_utils.c                  \
		ft_flags_handler.c               \
		ft_invalid_format.c              \
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