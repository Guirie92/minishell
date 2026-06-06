/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:09:25 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 00:34:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "errno.h"
#include "error/error.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static void	write_in_heredoc(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	process_heredoc(t_data *data, t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit_with_error(data);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			if (errno == ENOMEM)
				exit_with_error(data);
			print_warning_arg(ERR_HEREDOC_EOF, redir->target);
			break ;
		}
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		write_in_heredoc(fd[1], line);
		free(line);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
}

void	heredoc_collector(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->pipeline->cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
				process_heredoc(data, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
