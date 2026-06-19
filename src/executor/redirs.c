/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:32:55 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 13:45:07 by guillsan         ###   ########.fr       */
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

static void	handle_redir_in(t_data *data, t_redir *redir, int read_fd)
{
	read_fd = open(redir->target, O_RDONLY);
	if (read_fd < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		exit(EXIT_FAILURE);
	}
	dup2(read_fd, STDIN_FILENO);
	close (read_fd);
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
static void	handle_redir_out(t_data *data, t_redir *redir, int next_pipe[2])
{
	next_pipe[1] = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (next_pipe[1] < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		exit(EXIT_FAILURE);
	}
	dup2(next_pipe[1], STDOUT_FILENO);
	close(next_pipe[1]);
}

static void	handle_redir_append(t_data *data, t_redir *redir, int next_pipe[2])
{
	next_pipe[1] = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (next_pipe[1] < 0)
	{
		print_error_arg(ERR_OPEN, redir->target);
		clear_data(data);
		exit(EXIT_FAILURE);
	}
	dup2(next_pipe[1], STDOUT_FILENO);
	close(next_pipe[1]);
}

static void	handle_redir_heredoc(t_redir *redir, int read_fd, int next_pipe[2])
{
	(void)redir;
	(void)read_fd;
	(void)next_pipe;
}

void	handle_redirs(t_data *data, t_cmd *cmd, int read_fd, int next_pipe[2])
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_redir_in(data, redir, read_fd);
		else if (redir->type == REDIR_OUT)
			handle_redir_out(data, redir, next_pipe);
		else if (redir->type == APPEND)
			handle_redir_append(data, redir, next_pipe);
		else if (redir->type == HEREDOC)
			handle_redir_heredoc(redir, read_fd, next_pipe);
		redir = redir->next;
	}
}
