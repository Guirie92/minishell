/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:35:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:17:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

typedef enum e_err_type
{
	ERR_MALLOC,
	ERR_CMD_NOT_FOUND,
	ERR_PERMISSION,
	ERR_PIPE_FAIL,
	ERR_COUNT,
	ERR_NO_MSG
}	t_err_type;

typedef struct s_data	t_data;

void	exit_with_error(t_data *data, t_err_type err_code);

#endif /* ERROR_HANDLER_H */