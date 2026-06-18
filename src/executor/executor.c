/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:26:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/18 21:25:30 by guillsan         ###   ########.fr       */
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

static int create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		print_error(ERR_PIPE);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}

static int fork_child_process(t_cmd *cmd, int read_fd, int next_fd[2])
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

/*
 * If there's no argv[0], or if it's an empty string, such as in only
 * redirections, it just exits without calling execve
 */
static void	execute_command(t_data *data, t_cmd *cmd)
{
	char	**envp;

	if (!cmd->argv || !cmd->argv[0])
	{
		clear_data(data);
		exit(EXIT_SUCCESS);
	}
	set_path(data, cmd);
	if (!cmd->path)
	{
		if (ft_strchr(cmd->argv[0], '/'))
			print_error_arg(ERR_NO_FILE_OR_DIR, cmd->argv[0]);
		else
			print_error_arg(ERR_CMD_NOT_FOUND, cmd->argv[0]);
		clear_data(data);
		exit(EXIT_CMD_NOT_FOUND);
	}
	envp = env_to_envp(data);
	execve(cmd->path, cmd->argv, envp);
	free_envp(envp);
}

static void process_cmd_in_child(t_data *data, t_cmd *cmd, int read_fd,
	int next_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
	if (cmd->next)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		close(next_fd[1]);
	}
	execute_command(data, cmd);
	if (errno == EACCES)
	{
		print_error_arg(ERR_PERMISSION_DENIED, cmd->argv[0]);
		exit(EXIT_PERMISSION_DENIED);
	}
	else if (errno == ENOENT)
		print_error_arg(ERR_NO_FILE_OR_DIR, cmd->argv[0]);
	else
		perror(cmd->argv[0]);
	exit(EXIT_CMD_NOT_FOUND);
}

static void	handle_pipes(t_cmd *cmd, int *read_fd, int next_pipe[2])
{
	if (*read_fd != STDIN_FILENO)
		close(*read_fd);
	if (cmd->next)
	{
		close(next_pipe[1]);
		*read_fd = next_pipe[0];
	}
}

static void process_commands(t_data *data, t_cmd *cmd, int next_pipe[2])
{
	int	read_fd;

	read_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
			if (create_pipe(next_pipe) != E_SUCCESS)
				break ;
		if (handle_redirs(cmd, &read_fd, next_pipe) != E_SUCCESS)
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

	cmd = data->pipeline->cmds;
	next_pipe[0] = -1;
	next_pipe[1] = -1;
	process_commands(data, cmd, next_pipe);
	signal(SIGINT, SIG_IGN);
	wait_for_child_processes(data);
	signal(SIGINT, sigint_handler);
}
