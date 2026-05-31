/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:09:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 20:12:29 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer_internal.h"

void	add_token(t_data *data, t_lexer *lx, t_token_type token_type)
{
	t_token	*token;

	lx->buffer[lx->buf_idx] = '\0';
	if (lx->buffer[0] == '\0' && token_type == TOKEN_WORD && !lx->b_quoted)
	{
		lx->b_quoted = FALSE;	
		return ;
	}
	token = malloc(sizeof(*token));
	if (!token)
		exit_lexer_with_error(data, lx);
	token->type = token_type;
	token->value = ft_strdup(lx->buffer);
	if (!token->value)
	{
		free(token);
		exit_lexer_with_error(data, lx);
	}
	token->next = NULL;
	if (lx->head == NULL)
	{
		lx->head = token;
		data->tokens_head = token;
	}
	else
		lx->tail->next = token;
	lx->tail = token;
	reset_buffer(lx);
}

static void	process_operator(t_data *data, t_lexer *lx)
{
	const int	i = lx->input_idx;
	
	if (lx->buf_idx > 0)
		add_token(data, lx, TOKEN_WORD);
	if (lx->input[i] == '|')
		add_token(data, lx, TOKEN_PIPE);
	else if (lx->input[i] == '>' && lx->input[i + 1] == '>')
	{
		(lx->input_idx)++;
		add_token(data, lx, TOKEN_APPEND);
	}
	else if (lx->input[i] == '<' && lx->input[i + 1] == '<')
	{
		(lx->input_idx)++;
		add_token(data, lx, TOKEN_HEREDOC);
	}
	else if (lx->input[i] == '>')
		add_token(data, lx, TOKEN_REDIR_OUT);
	else if (lx->input[i] == '<')
		add_token(data, lx, TOKEN_REDIR_IN);
}

void	process_lx_normal(t_data *data, t_lexer *lx)
{
	if (ft_isspace(lx->input[lx->input_idx]))
		add_token(data, lx, TOKEN_WORD);
	else if (lx->input[lx->input_idx] == '\'')
		lx->state = LEXER_SINGLE_QUOTE;
	else if (lx->input[lx->input_idx] == '"')
		lx->state = LEXER_DOUBLE_QUOTE;
	else if (ft_strrchr(LEXER_OPERATORS, lx->input[lx->input_idx]) != NULL)
		process_operator(data, lx);
	else
	{
		lx->buffer[lx->buf_idx] = lx->input[lx->input_idx];
		(lx->buf_idx)++;	
	}
}

void	process_lx_single_q(t_lexer *lx)
{
	if (lx->input[lx->input_idx] == '\'')
	{
		lx->state = LEXER_NORMAL;
		lx->b_quoted = TRUE;
	}
	else
		lx->buffer[lx->buf_idx++] = lx->input[lx->input_idx];
}

void	process_lx_double_q(t_lexer *lx)
{
	if (lx->input[lx->input_idx] == '"')
	{
		lx->state = LEXER_NORMAL;
		lx->b_quoted = TRUE;
	}
	else
		lx->buffer[lx->buf_idx++] = lx->input[lx->input_idx];
}
