/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:32:43 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/18 21:39:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "clear_resources/clear_resources.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

const char	*errmsg(t_err_type id)
{
	const char	*err_msg[ERR_COUNT] = {
	[ERR_UNCLOSED_QUOTES] = "syntax error: unclosed quote",
	[ERR_INVALID_REDIR] = "syntax error: invalid redirection",
	[ERR_UNEXPECTED_TOKEN] = "syntax error near unexpected token '%s'",
	[ERR_HEREDOC_EOF] = ("warning: here-document at line 1 delimited by "
			"end-of-file (wanted '%s')"),
	[ERR_CMD_NOT_FOUND] = "command not found: %s",
	[ERR_NO_FILE_OR_DIR] = "no such file or directory: %s",
	[ERR_PERMISSION_DENIED] = "permission denied: %s",
	[ERR_PIPE] = "pipe failed",
	[ERR_FORK] = "fork failed",
	};

	if (id < 0 || id >= ERR_COUNT)
		return ("unknown error");
	return (err_msg[id]);
}

void	print_error(t_err_type err)
{
	const char	*err_msg = errmsg(err);

	ft_dprintf(STDERR_FILENO, ERROR_CLR ERR_MINISHELL_PREFIX
		"%s\n" CLR_RST, err_msg);
}

void	print_error_arg(t_err_type err, char *arg)
{
	const char	*err_msg = errmsg(err);

	ft_dprintf(STDERR_FILENO, ERROR_CLR ERR_MINISHELL_PREFIX);
	ft_dprintf(STDERR_FILENO, err_msg, arg);
	ft_dprintf(STDERR_FILENO, "\n" CLR_RST);
}

void	print_sys_error(void)
{
	const int	saved_errno = errno;
	char		*sys_err;

	if (saved_errno != 0)
	{
		sys_err = strerror(saved_errno);
		ft_dprintf(STDERR_FILENO, ERROR_CLR ERR_MINISHELL_PREFIX
			"%s\n" CLR_RST, sys_err);
	}
}

void	exit_with_error(t_data *data)
{
	const int	saved_errno = errno;
	char		*sys_err;

	if (saved_errno != 0)
	{
		sys_err = strerror(saved_errno);
		ft_dprintf(STDERR_FILENO, ERROR_CLR "%s\n" CLR_RST, sys_err);
	}
	clear_data(data);
	exit(EXIT_FAILURE);
}
