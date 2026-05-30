/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:32:43 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:39:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clear_resources/clear_resources.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

void	exit_with_error(t_data *data, t_err_type err_code)
{
	const int	saved_errno = errno;
	char		*sys_err;
	const char	*err_msg[] = {
	[ERR_MALLOC] = "Memory allocation failed",
	[ERR_CMD_NOT_FOUND] = "Command not found",
	[ERR_PERMISSION] = "Permission denied",
	[ERR_PIPE_FAIL] = "Pipe failed"
	};

	if (err_code >= 0 && err_code < ERR_COUNT)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, err_msg[err_code], ft_strlen(err_msg[err_code]));
		write(STDERR_FILENO, "\n", 1);
	}
	if (saved_errno != 0)
	{
		sys_err = strerror(saved_errno);
		write(STDERR_FILENO, sys_err, ft_strlen(sys_err));
		write(STDERR_FILENO, "\n", 1);
	}
	clear_data(data);
	exit(EXIT_FAILURE);
}
