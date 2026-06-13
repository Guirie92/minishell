/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:09:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 12:30:46 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer/lexer_internal.h"

void	add_token(t_data *data, t_lexer *lx, t_token_type token_type,
	t_token_mode allow_empty)
{
	t_token	*token;

	lx->buffer[lx->buf_idx] = '\0';
	if (lx->buf_idx == 0 && token_type == TOKEN_WORD && !allow_empty)
		return ;
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
		data->tokens = token;
	}
	else
		lx->tail->next = token;
	lx->tail = token;
	reset_buffer(lx);
}

static void	process_operator(t_data *data, t_lexer *lx)
{
	const size_t	i = lx->input_idx;

	if (lx->buf_idx > 0)
		add_token(data, lx, TOKEN_WORD, TOKEN_DEFAULT);
	if (lx->input[i] == '|')
		add_token(data, lx, TOKEN_PIPE, TOKEN_DEFAULT);
	else if (lx->input[i] == '>' && lx->input[i + 1] == '>')
	{
		(lx->input_idx)++;
		add_token(data, lx, TOKEN_APPEND, TOKEN_DEFAULT);
	}
	else if (lx->input[i] == '<' && lx->input[i + 1] == '<')
	{
		(lx->input_idx)++;
		add_token(data, lx, TOKEN_HEREDOC, TOKEN_DEFAULT);
	}
	else if (lx->input[i] == '>')
		add_token(data, lx, TOKEN_REDIR_OUT, TOKEN_DEFAULT);
	else if (lx->input[i] == '<')
		add_token(data, lx, TOKEN_REDIR_IN, TOKEN_DEFAULT);
}

void	process_lx_normal(t_data *data, t_lexer *lx)
{
	if (ft_isspace(lx->input[lx->input_idx]))
		add_token(data, lx, TOKEN_WORD, TOKEN_DEFAULT);
	else if (ft_strrchr(LEXER_OPERATORS, lx->input[lx->input_idx]) != NULL)
		process_operator(data, lx);
	else
	{
		if (lx->input[lx->input_idx] == '\'')
			lx->state = QUOTE_CONTEXT_SINGLE;
		else if (lx->input[lx->input_idx] == '"')
			lx->state = QUOTE_CONTEXT_DOUBLE;
		lx->buffer[lx->buf_idx] = lx->input[lx->input_idx];
		(lx->buf_idx)++;
	}
}

void	process_lx_single_q(t_data *data, t_lexer *lx)
{
	const size_t	i = lx->input_idx;

	if (lx->input[i] == '\'')
	{
		lx->buffer[lx->buf_idx] = lx->input[lx->input_idx];
		(lx->buf_idx)++;
		lx->state = QUOTE_CONTEXT_NORMAL;
		if (lx->buf_idx == 0
			&& (ft_isspace(lx->input[i + 1]) || lx->input[i + 1] == '\0'
				|| ft_strrchr(LEXER_OPERATORS, lx->input[i + 1]) != NULL))
			add_token(data, lx, TOKEN_WORD, TOKEN_ALLOW_EMPTY);
	}
	else
		lx->buffer[lx->buf_idx++] = lx->input[lx->input_idx];
}

void	process_lx_double_q(t_data *data, t_lexer *lx)
{
	const size_t	i = lx->input_idx;

	if (lx->input[lx->input_idx] == '"')
	{
		lx->buffer[lx->buf_idx] = lx->input[lx->input_idx];
		(lx->buf_idx)++;
		lx->state = QUOTE_CONTEXT_NORMAL;
		if (lx->buf_idx == 0
			&& (ft_isspace(lx->input[i + 1]) || lx->input[i + 1] == '\0'
				|| ft_strrchr(LEXER_OPERATORS, lx->input[i + 1]) != NULL))
			add_token(data, lx, TOKEN_WORD, TOKEN_ALLOW_EMPTY);
	}
	else
		lx->buffer[lx->buf_idx++] = lx->input[lx->input_idx];
}
