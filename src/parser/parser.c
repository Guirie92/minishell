/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:46:37 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 19:26:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/parser_internal.h"

static int	is_redir(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

static int	validate_current_cmd(t_data *data, t_token *token)
{
	if (data->tokens_head->type == TOKEN_PIPE)
	{
		custom_error_msg(ERR_LEADING_PIPE);
		return (E_FAILURE);
	}
	else if (!token->next)
	{
		custom_error_msg(ERR_TRAILING_PIPE);
		return (E_FAILURE);
	}
	else if (token->next->type == TOKEN_PIPE)
	{
		custom_error_msg(ERR_MULTIPLE_PIPES);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}

static int	parse_redir(t_data *data, t_cmd *cmd, t_token **in_token)
{
	t_redir	*redir;

	if (!(*in_token)->next || (*in_token)->next->type != TOKEN_WORD)
	{
		custom_error_msg(ERR_INVALID_REDIR);	
		return (E_FAILURE);
	}
	redir = init_redir(data);
	add_redir(data, cmd, redir, (*in_token));
	*in_token = (*in_token)->next;
	return (E_SUCCESS);
}

static int	parser_input(t_data *data, t_token *token)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = init_cmd(data);
	data->pipeline->cmds = cmd;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			add_arg(data, cmd, token->value);
		else if (is_redir(token))
		{
			if (parse_redir(data, cmd, &token) != E_SUCCESS)
				return (E_FAILURE);
		}
		else if (token->type == TOKEN_PIPE)
		{
			if (validate_current_cmd(data, token) != E_SUCCESS)
				return (E_FAILURE);
			tmp = init_cmd(data);
			cmd->next = tmp;
			cmd = tmp;
		}
		token = token->next;
	}
	return (E_SUCCESS);
}

int	parser(t_data *data)
{
	t_pipeline	*pipeline;
	t_token		*token;

	token = data->tokens_head;
	pipeline = malloc(sizeof(*pipeline));
	if (!pipeline)
		exit_with_error(data, ERR_SYTEM_MSG);
	pipeline->cmds = NULL;
	data->pipeline = pipeline;
	if (parser_input(data, token) != E_SUCCESS)
		return (E_FAILURE);
	heredoc_collector(data);
	return (E_SUCCESS);
}
