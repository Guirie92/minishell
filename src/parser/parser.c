/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:46:37 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/05 15:18:51 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

static int	is_redir(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

static void	parser_input(t_data *data, t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
			add_arg(data, token->value);
		else if (is_redir(token))
			parse_redir(data, token);
		else if (token->type == TOKEN_PIPE)
		{
			validate_current_cmd(data, token);
			push_cmd(data->pipeline);
		}
		token = token->next;
	}
}

void	parser(t_data *data)
{
	t_pipeline	*pipeline;
	t_token	*token;
	
	token = data->tokens_head;
	pipeline = malloc(sizeof(*pipeline));
	if (!pipeline)
		exit_with_error(data, ERR_NO_MSG);
	pipeline->cmds = NULL;
	pipeline->cmdc = 0;
	data->pipeline = pipeline;
	parser_input(data, token);
}
