/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:35:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 20:17:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# define WARNING_CLR      "\033[33m"
# define ERROR_CLR        "\033[31m"

typedef enum e_err_type
{
	ERR_NONE,
	ERR_UNCLOSED_QUOTES,
	ERR_INVALID_REDIR,
	ERR_LEADING_PIPE,
	ERR_TRAILING_PIPE,
	ERR_MULTIPLE_PIPES,
	ERR_MALLOC,
	ERR_CMD_NOT_FOUND,
	ERR_PERMISSION,
	ERR_PIPE_FAIL,
	ERR_COUNT,
	ERR_SYTEM_MSG
}	t_err_type;

typedef struct s_data	t_data;

void	custom_error_msg(t_err_type err_code);
void	exit_with_error(t_data *data, t_err_type err_code);
void	exit_with_error_msg(t_data *data, char *err_msg);
void	error_msg(char *err_msg);

#endif /* ERROR_HANDLER_H */