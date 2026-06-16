/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:26:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 17:08:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"

static char	*get_path(t_data *data, t_cmd *cmd)
{
	char	**path_list;
	char	*path;

	if (ft_strchr(cmd->argv[0], '/'))
		return (cmd->argv[0]);

	// TODO: path and path_list with split delimiter ':' on $PATH
	(void)path_list;
	(void)path;
	(void)data;
	
	// END TODO

	
	return (path);
}

static void	process_command(t_data *data, t_cmd *cmd)
{
	char	**envp;
	char	*path;

	envp = env_to_envp(data);
	path = get_path(data, cmd);
	execve(path, cmd->argv, envp);
	free_envp(envp);
	free(path);
}

void	execute(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->pipeline->cmds;
	while (cmd)
	{
		process_command(data, cmd);
		cmd = cmd->next;
	}
}
