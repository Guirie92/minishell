/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:26:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/17 22:27:21 by guillsan         ###   ########.fr       */
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

	cmd = data->pipeline->cmds;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_status = 128 + WTERMSIG(status);
			cmd->pid = -1;
		}
		cmd = cmd->next;
	}
}

static int create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		print_error(ERR_PIPE);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}

static int fork_child_process(t_cmd *cmd, int input_fd, int next_fd[2])
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		print_error(ERR_FORK);
		if (next_fd[0] != -1)
			close(next_fd[0]);
		if (next_fd[1] != -1)
			close(next_fd[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}

static void	process_command(t_data *data, t_cmd *cmd)
{
	char	**envp;

	set_path(data, cmd);
	if (!cmd->path)
	{
		if (!cmd->argv)
			print_error(ERR_CMD_NOT_FOUND);
		else if (ft_strchr(cmd->argv[0], '/'))
			print_error_arg(ERR_NO_FILE_OR_DIR, cmd->argv[0]);
		else
			print_error_arg(ERR_CMD_NOT_FOUND_ARG, cmd->argv[0]);
		clear_data(data);
		exit(EXIT_CMD_NOT_FOUND);
	}
	envp = env_to_envp(data);
	execve(cmd->path, cmd->argv, envp);
	free_envp(envp);
}

static void process_cmd_in_child(t_data *data, t_cmd *cmd, int input_fd,
	int next_fd[2])
{
	//if (input_fd != -1)
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (cmd->next)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		close(next_fd[1]);
	}
	process_command(data, cmd);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	execute(t_data *data)
{
	t_cmd	*cmd;
	int		input_fd;
	int		next_pipe[2];

	cmd = data->pipeline->cmds;
	input_fd = STDIN_FILENO;
	next_pipe[0] = -1;
	next_pipe[1] = -1;
	while (cmd)
	{
		if (cmd->next)
			if (create_pipe(next_pipe) != E_SUCCESS)
				break ;
		if (fork_child_process(cmd, input_fd, next_pipe) != E_SUCCESS)
			break ;

		//printf("pid: %d\n", cmd->pid);
		if (cmd->pid == 0)
			process_cmd_in_child(data, cmd, input_fd, next_pipe);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (cmd->next)
		{
			close(next_pipe[1]);
			input_fd = next_pipe[0];
		}
		cmd = cmd->next;
	}
	wait_for_child_processes(data);
}
