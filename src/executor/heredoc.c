/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:09:25 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 14:09:27 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "string_builder/string_builder.h"
#include "parser/parser.h"
#include "expander/expander.h"
#include "executor/executor_internal.h"
#include "clear_resources/clear_resources.h"
#include "errno.h"
#include "error/error.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>

static void	write_line_fd(char *line, int fd[2])
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

static char	*handle_expansion(t_data *data, t_redir *redir, char *line)
{
	size_t	len;
	char	*expanded_line;
	int		b_has_expanded;

	if (!redir->should_expand_hd)
		return (line);
	b_has_expanded = 0;
	len = calculate_expanded_len(data, line, &b_has_expanded);
	if (!b_has_expanded)
		return (line);
	expanded_line = malloc((len + 1) * sizeof(char));
	if (!expanded_line)
	{
		free(line);
		exit_with_error(data);
	}
	fill_expanded_line(data, line, expanded_line);
	return (expanded_line);
}

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
		line = handle_expansion(data, redir, line);
		write_line_fd(line, fd);
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
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_loop(data, redir, fd, prompt);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(data, status);
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
