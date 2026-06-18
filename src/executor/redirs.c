/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:32:55 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/18 21:37:16 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error/error.h"
#include <fcntl.h>
#include "parser/parser.h"

static int	handle_redir_in(t_redir *redir, int *read_fd)
{
	int	fd;

	// fd = open(redir->target, O_RDONLY);
	fd = open("", O_RDONLY);
	(void)redir;
	if (fd < 0)
	{
		print_sys_error();
		return (E_FAILURE);
	}
	dup2(fd, *read_fd);
	close (fd);
	return (E_SUCCESS);
}

static int	handle_redir_out(t_redir *redir, int *read_fd, int next_pipe[2])
{
	(void)redir;
	(void)read_fd;
	(void)next_pipe;
	return (E_SUCCESS);
}

static int	handle_redir_append(t_redir *redir, int *read_fd, int next_pipe[2])
{
	(void)redir;
	(void)read_fd;
	(void)next_pipe;
	return (E_SUCCESS);
}

static int	handle_redir_heredoc(t_redir *redir, int *read_fd, int next_pipe[2])
{
	(void)redir;
	(void)read_fd;
	(void)next_pipe;
	return (E_SUCCESS);
}

int	handle_redirs(t_cmd *cmd, int *read_fd, int next_pipe[2])
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (handle_redir_in(redir, read_fd) != E_SUCCESS)
				return (E_FAILURE);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (handle_redir_out(redir, read_fd, next_pipe) != E_SUCCESS)
				return (E_FAILURE);
		}
		else if (redir->type == APPEND)
		{
			if (handle_redir_append(redir, read_fd, next_pipe) != E_SUCCESS)
				return (E_FAILURE);
		}
		else if (redir->type == HEREDOC)
		{
			if (handle_redir_heredoc(redir, read_fd, next_pipe) != E_SUCCESS)
				return (E_FAILURE);
		}
		redir = redir->next;
	}
	return (E_SUCCESS);
}
