/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:09:25 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 20:55:27 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "errno.h"
#include "error_handler/error_handler.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static void	write_in_heredoc(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void print_heredoc_warning(char *delimiter)
{
	write(STDERR_FILENO, "minishell: warning: here-document at line 1 ", 44);
	write(STDERR_FILENO, "delimited by end-of-file (wanted '", 34);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", 3);
}

static void	process_heredoc(t_data *data, t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit_with_error(data, ERR_SYTEM_MSG);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			if (errno == ENOMEM)
				exit_with_error(data, ERR_SYTEM_MSG);
			print_heredoc_warning(redir->target);
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
