/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:44:54 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 17:49:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

int	fork_child_process(t_cmd *cmd, int read_fd, int next_fd[2])
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		print_error(ERR_FORK);
		if (next_fd[0] != -1)
			close(next_fd[0]);
		if (next_fd[1] != -1)
			close(next_fd[1]);
		if (read_fd != STDIN_FILENO)
			close(read_fd);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}
