/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:09:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 13:26:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer_internal.h"

static void	reset_buffer(t_lexer *lx)
{
	lx->buf_idx = 0;
	lx->buffer[lx->buf_idx] = '\0';
}
static void	add_token(t_data *data, t_lexer *lx, t_token_type token_type)
{
	t_token	*token;

	lx->buffer[lx->buf_idx] = '\0';
	token = malloc(sizeof(*token));
	if(!token)
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

void	process_lx_normal(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
	add_token(data, lx, TOKEN_WORD);
	// TODO
	
}

void	process_lx_single_q(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
	// TODO
}

void	process_lx_double_q(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
	// TODO
}
