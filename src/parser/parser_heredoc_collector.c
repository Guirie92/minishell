/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_collector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:09:25 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 18:28:17 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

static void	process_heredoc(t_redir *redir)
{
	int	fd[2];

	pipe(fd);
	while ()
	{
		// TODO: readline
	}
}

void	heredoc_collector(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;
	
	cmd = data->pipeline->cmds;
	redir = cmd->redirs;
	while (cmd)
	{
		while (redir)
		{
			if (redir->type == HEREDOC)
				process_heredoc(redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
