/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:32:55 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 20:57:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * https://man7.org/linux/man-pages/man2/open.2.html
 * https://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html
 * 
 * The o-flags for open allows you to read, write, append or write from 0, etc.
 * 
 * The o-flags can be stacked back to back with a pipe '|' 
 * (OR operator in bitwise operations).
 * 
 * The reason why this work is because the int numbers for the flags are a
 * representation of a bitmask
 */

#include "minishell.h"
#include "error/error.h"
#include <fcntl.h>
#include "parser/parser.h"

static int	handle_redir_in(t_data *data, t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		return (E_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (E_SUCCESS);
}

/*
 * https://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html
 * 
 * The signature of open is:
 * 
 * `int open(const char *path, int oflag, ... );`
 * 
 * `va args`, like in printf, is why it can accept 2 or more arguments.
 * 
 * As for flags (oflag, 2nd parameter), you can placed various flags, such as
 * `O_WRONLY | O_CREAT | O_TRUNC` back to back to back, since it's creating a
 * bit mask that represents the final integer variable
 * (common in system programming).
 * 
 * For example, in this case:
 * O_WRONLY  1 --> 0001
 * O_CREAT  64 --> 0100 0000
 * O_TRUNC 512 --> 0010 0000 0000
 * 
 * result: 0010 0100 0001 (single integer passed)
 * 
 * In addition, when O_CREAT is marked, a 3rd argument is necessary
 * to specify the permissions needed for creating that new file, in octal
 * (thus the leading 0 in 0644 just to express the number 
 * in octal representation).
 * 
 * For example, 0644:
 * - owner:  6 --> rw-
 * - group:  4 --> r--
 * - others: 4 --> r--
 */
static int	handle_redir_out(t_data *data, t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		return (E_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (E_SUCCESS);
}

static int	handle_redir_append(t_data *data, t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		return (E_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (E_SUCCESS);
}

static int	handle_redir_heredoc(t_data *data, t_redir *redir)
{
	if (redir->heredoc_fd < 0)
	{
		print_error_arg(ERR_OPEN, "heredoc");
		clear_data(data);
		return (E_FAILURE);
	}
	dup2(redir->heredoc_fd, STDIN_FILENO);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (E_SUCCESS);
}

int	handle_redirs(t_data *data, t_cmd *cmd)
{
	t_redir	*redir;
	int		ret_code;

	redir = cmd->redirs;
	ret_code = E_SUCCESS;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			ret_code = handle_redir_in(data, redir);
		else if (redir->type == REDIR_OUT)
			ret_code = handle_redir_out(data, redir);
		else if (redir->type == APPEND)
			ret_code = handle_redir_append(data, redir);
		else if (redir->type == HEREDOC)
			ret_code = handle_redir_heredoc(data, redir);
		if (ret_code != E_SUCCESS)
			return (ret_code);
		redir = redir->next;
	}
	return (E_SUCCESS);
}
