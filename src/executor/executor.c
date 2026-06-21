/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:26:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 17:49:06 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"
#include "executor/executor_internal.h"

static void	wait_for_child_processes(t_data *data)
{
	t_cmd	*cmd;
	int		status;
	int		b_signaled;

	cmd = data->pipeline->cmds;
	b_signaled = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
					b_signaled = 1;
			}
			if (!cmd->next)
				update_exit_status(data, status);
			cmd->pid = -1;
		}
		cmd = cmd->next;
	}
	if (b_signaled)
		write(1, "\n", 1);
}

static void	process_parent_builtin(t_data *data, t_cmd *cmd)
{
	data->saved_fd[0] = dup(STDIN_FILENO);
	data->saved_fd[1] = dup(STDOUT_FILENO);
	if (handle_redirs(data, cmd) != E_SUCCESS)
		data->exit_status = 1;
	else
		process_builtin(data, cmd);
	dup2(data->saved_fd[0], STDIN_FILENO);
	dup2(data->saved_fd[1], STDOUT_FILENO);
	close(data->saved_fd[0]);
	close(data->saved_fd[1]);
	data->saved_fd[0] = -1;
	data->saved_fd[1] = -1;
}

static void process_commands(t_data *data, t_cmd *cmd, int next_pipe[2])
{
	int	read_fd;

	read_fd = STDIN_FILENO;
	if (!cmd->next && cmd->argv && is_builtin(data, cmd->argv[0]))
	{
		process_parent_builtin(data, cmd);
		return ;
	}
	while (cmd)
	{
		if (cmd->next)
			if (create_pipe(next_pipe) != E_SUCCESS)
				break ;
		if (fork_child_process(cmd, read_fd, next_pipe) != E_SUCCESS)
			break ;
		if (cmd->pid == 0)
			process_cmd_in_child(data, cmd, read_fd, next_pipe);
		handle_pipes(cmd, &read_fd, next_pipe);
		cmd = cmd->next;
	}
}

void	execute(t_data *data)
{
	t_cmd	*cmd;
	int		next_pipe[2];

	if (!data->pipeline->cmds)
        return ;
	cmd = data->pipeline->cmds;
	next_pipe[0] = -1;
	next_pipe[1] = -1;
	process_commands(data, cmd, next_pipe);
	signal(SIGINT, SIG_IGN);
	wait_for_child_processes(data);
	signal(SIGINT, sigint_handler);
}
