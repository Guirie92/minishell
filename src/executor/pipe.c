/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:45:01 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 17:51:29 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

void	handle_pipes_child(t_cmd *cmd, int read_fd, int next_pipe[2])
{
	if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
	if (cmd->next)
	{
		close(next_pipe[0]);
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
	}
}

void	handle_pipes(t_cmd *cmd, int *read_fd, int next_pipe[2])
{
	if (*read_fd != STDIN_FILENO)
		close(*read_fd);
	if (cmd->next)
	{
		close(next_pipe[1]);
		*read_fd = next_pipe[0];
	}
}

int create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		print_error(ERR_PIPE);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}
