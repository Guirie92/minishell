/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:39:59 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/05 16:06:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser/parser.h"
#include "clear_resources/clear_resources.h"

static void	free_cmds(t_cmd *cmd)
{
	t_redir	*next;
	int		i;

	if (!cmd)
		return ;
	i = 0;
	if (cmd->argv)
	{
		while (i < cmd->argc)
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	while (cmd->redirs)
	{
		free(cmd->redirs->target);
		if (cmd->redirs->type == HEREDOC && cmd->redirs->heredoc_fd != -1)
			close(cmd->redirs->heredoc_fd);
		next = cmd->redirs->next;
		free(cmd->redirs);
		cmd->redirs = next;
	}
}

void	free_pipeline(t_data *data)
{
	t_cmd	*next;
	
	if (!data || !data->pipeline)
		return ;
	while (data->pipeline->cmds)
	{
		next = data->pipeline->cmds->next;
		free_cmds(data->pipeline->cmds);
		free(data->pipeline->cmds);
		data->pipeline->cmds = next;
	}
	free(data->pipeline);
	data->pipeline = NULL;
}
