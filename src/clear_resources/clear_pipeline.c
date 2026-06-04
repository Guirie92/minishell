/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:39:59 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/04 14:45:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser/parser.h"
#include "clear_resources/clear_resources.h"

static void	free_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
		free(cmd->argv[i++]);
	free(cmd->argv);
	i = 0;
	while (i < cmd->redirc)
	{
		free(cmd->redirs[i].target);
		if (cmd->redirs[i].type == HEREDOC && cmd->redirs[i].heredoc_fd != -1)
			close(cmd->redirs[i].heredoc_fd);
		cmd->redirs[i++].heredoc_fd = -1;
	}
	free(cmd->redirs);
}

void	free_pipeline(t_data *data)
{
	int	i;
	
	i = 0;
	if (!data->pipeline)
		return ;
	while (i < data->pipeline->cmdsc)
		free_cmds(&data->pipeline->cmds[i]);
	free(data->pipeline->cmds);
	free(data->pipeline);
	data->pipeline = NULL;
}
