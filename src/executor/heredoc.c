/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:09:25 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 15:25:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_builder/string_builder.h"
#include "parser/parser.h"
#include "executor/executor_internal.h"
#include "clear_resources/clear_resources.h"
#include "errno.h"
#include "error/error.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static void	heredoc_loop(t_data *data, t_redir *redir, int fd[2], char *prompt)
{
	char	*line;

	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			if (errno == ENOMEM)
				heredoc_exit(data, fd, HD_FAILURE);
			print_warning_arg(ERR_HEREDOC_EOF, redir->target);
			heredoc_exit(data, fd, HD_EOF);
		}
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[0]);
	close(fd[1]);
	clear_data(data);
	exit(HD_SUCCESS);
}

static int	process_heredoc(t_data *data, t_redir *redir, char *prompt)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		exit_with_error(data);
	pid = fork();
	if (pid == -1)
		exit_with_error(data);
	g_signal = S_HD;
	if (pid == 0)
		heredoc_loop(data, redir, fd, prompt);
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	waitpid(pid, &status, 0);
	g_signal = S_DEFAULT;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (E_FAILURE);
	if (check_hd_exit_status(data, status) != HD_SUCCESS)
		return (E_FAILURE);
	return (E_SUCCESS);
}

int	heredoc_collector(t_data *data)
{
	t_redir		*redir;
	t_cmd		*cmd;
	t_builder	sb;
	int			heredoc_idx;

	heredoc_idx = 0;
	cmd = data->pipeline->cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				build_hd_prompt(&sb, heredoc_idx);
				heredoc_idx++;
				if (process_heredoc(data, redir, sb.buf) == E_FAILURE)
					return (E_FAILURE);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (E_SUCCESS);
}
