/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:32:43 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 12:03:22 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clear_resources/clear_resources.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

static void	write_error(char *msg, size_t len)
{
	write(STDERR_FILENO, ERROR_CLR, 5);
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, ERROR_CLR_RESET, 4);
	write(STDERR_FILENO, "\n", 1);
}

void	custom_error_msg(t_err_type err_code)
{
	const char	*err_msg[] = {
	[ERR_NONE] = "",
	[ERR_UNCLOSED_QUOTES] = "syntax error: unclosed quote",
	[ERR_INVALID_REDIR] = "syntax error: invalid redirection",
	[ERR_LEADING_PIPE] = "syntax error near unexpected token '|'",
	[ERR_TRAILING_PIPE] = "syntax error near unexpected token '|'",
	[ERR_MULTIPLE_PIPES] = "syntax error near unexpected token '|'",
	[ERR_MALLOC] = "Memory allocation failed",
	[ERR_CMD_NOT_FOUND] = "Command not found",
	[ERR_PERMISSION] = "Permission denied",
	[ERR_PIPE_FAIL] = "Pipe failed"
	};

	if (err_code < ERR_COUNT)
		write_error((char *)err_msg[err_code], ft_strlen(err_msg[err_code]));
}

void	exit_with_error(t_data *data, t_err_type err_code)
{
	const int	saved_errno = errno;
	char		*sys_err;

	custom_error_msg(err_code);
	if (saved_errno != 0)
	{
		sys_err = strerror(saved_errno);
		write_error(sys_err, ft_strlen(sys_err));
	}
	clear_data(data);
	exit(EXIT_FAILURE);
}

void	exit_with_error_msg(t_data *data, char *err_msg)
{
	clear_data(data);
	write_error(err_msg, ft_strlen(err_msg));
	exit(EXIT_FAILURE);
}

void	error_msg(char *err_msg)
{
	write_error(err_msg, ft_strlen(err_msg));
}
