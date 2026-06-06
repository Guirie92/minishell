/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:31:29 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 19:26:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "lexer/lexer_internal.h"

void	exit_lexer_with_error(t_data *data, t_lexer *lx)
{
	if (lx->buffer)
		free(lx->buffer);
	lx->buffer = NULL;
	exit_with_error(data, ERR_SYTEM_MSG);
}

void	reset_buffer(t_lexer *lx)
{
	lx->buf_idx = 0;
	lx->buffer[lx->buf_idx] = '\0';
}

static int	init_lexer(t_data *data, t_lexer *lx)
{
	lx->input = data->line;
	lx->buffer = NULL;
	lx->head = NULL;
	lx->tail = NULL;
	lx->state = LEXER_NORMAL;
	lx->input_idx = 0;
	lx->buf_idx = 0;
	lx->state = LEXER_NORMAL;
	if (!lx->input)
		return (E_FAILURE);
	lx->buffer = malloc((ft_strlen(lx->input) + 1) * sizeof(char));
	if (!lx->buffer)
		exit_lexer_with_error(data, lx);
	return (E_SUCCESS);
}

static void	tokenize_input(t_data *data, t_lexer *lx)
{
	while (lx->input[lx->input_idx])
	{
		if (lx->state == LEXER_NORMAL)
			process_lx_normal(data, lx);
		else if (lx->state == LEXER_SINGLE_QUOTE)
			process_lx_single_q(data, lx);
		else if (lx->state == LEXER_DOUBLE_QUOTE)
			process_lx_double_q(data, lx);
		(lx->input_idx)++;
	}
	if (lx->buf_idx > 0)
		add_token(data, lx, TOKEN_WORD, TOKEN_DEFAULT);
}

int	lexer(t_data *data)
{
	t_lexer	lx;

	if (init_lexer(data, &lx) != E_SUCCESS)
		return (E_FAILURE);
	tokenize_input(data, &lx);
	if (lx.buffer)
		free(lx.buffer);
	lx.buffer = NULL;
	if (lx.state != LEXER_NORMAL)
	{
		custom_error_msg(ERR_UNCLOSED_QUOTES);
		return (E_FAILURE);
	}
	return (E_SUCCESS);
}
