/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:35:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/04 11:52:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# define ERROR_CLR        "\033[31m"
# define ERROR_CLR_RESET  "\033[0m"

typedef enum e_err_type
{
	ERR_NONE,
	ERR_UNCLOSED_QUOTES,
	ERR_MALLOC,
	ERR_CMD_NOT_FOUND,
	ERR_PERMISSION,
	ERR_PIPE_FAIL,
	ERR_COUNT,
	ERR_NO_MSG
}	t_err_type;

typedef struct s_data	t_data;

void	custom_error_msg(t_err_type err_code);
void	exit_with_error(t_data *data, t_err_type err_code);
void	exit_with_error_msg(t_data *data, char *err_msg);
void	error_msg(char *err_msg);

#endif /* ERROR_HANDLER_H */