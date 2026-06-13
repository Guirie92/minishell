/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:54:05 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 15:37:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"
#include "parser/parser_internal.h"
#include "lexer/lexer.h"

t_cmd	*init_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		exit_with_error(data);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->redir_tail = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}

t_redir	*init_redir(t_data *data)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	if (!redir)
		exit_with_error(data);
	redir->type = 0;
	redir->target = NULL;
	redir->heredoc_fd = -1;
	redir->should_expand_hd = 0;
	redir->next = NULL;
	return (redir);
}

static void	set_redir_type(t_redir_type *redir_type, t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		*redir_type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		*redir_type = REDIR_OUT;
	else if (token->type == TOKEN_APPEND)
		*redir_type = APPEND;
	else if (token->type == TOKEN_HEREDOC)
		*redir_type = HEREDOC;
}

void	add_redir(t_data *data, t_cmd *cmd, t_redir *redir, t_token *token)
{
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		cmd->redir_tail = redir;
	}
	else
	{
		cmd->redir_tail->next = redir;
		cmd->redir_tail = redir;
	}
	set_redir_type(&cmd->redir_tail->type, token);
	if (redir->type != HEREDOC)
	{
		redir->target = ft_strdup(token->next->value);
		if (!redir->target)
			exit_with_error(data);
	}
	else
		parse_heredoc_delimiter(data, redir, token->next->value);
}

void	add_arg(t_data *data, t_cmd *cmd, const char *s)
{
	size_t	old_size;
	size_t	new_size;
	char	**tmp;
	char	*str;

	old_size = (cmd->argc + 1) * sizeof(char *);
	new_size = (cmd->argc + 2) * sizeof(char *);
	tmp = ft_realloc(cmd->argv, old_size, new_size);
	if (!tmp)
		exit_with_error(data);
	(cmd->argc)++;
	cmd->argv = tmp;
	str = ft_strdup(s);
	if (!str)
		exit_with_error(data);
	cmd->argv[cmd->argc - 1] = str;
	cmd->argv[cmd->argc] = NULL;
}
