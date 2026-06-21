/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:02:43 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 18:45:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"
#include "builtins/builtins.h"
#include "executor/executor_internal.h"

/**
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
	if (process_builtin(data, cmd) == 1)
	{
		clear_data(data);
		exit(data->exit_status);
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

void process_cmd_in_child(t_data *data, t_cmd *cmd, int read_fd,
	int next_pipe[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_pipes_child(cmd, read_fd, next_pipe);
	if (handle_redirs(data, cmd) != E_SUCCESS)
	{
		clear_data(data);
		exit(EXIT_FAILURE);
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
