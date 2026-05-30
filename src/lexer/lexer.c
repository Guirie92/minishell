/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:31:29 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:21:21 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "lexer/lexer_internal.h"

static void	init_lexer(t_lexer *lx)
{
	lx->head = NULL;
	lx->tail = NULL;
	lx->state = LEXER_NORMAL;
	lx->input = NULL;
	lx->buffer = NULL;
	lx->pos = 0;
	lx->idx = 0;
}

static void	tokenize_input(t_data *data, t_lexer *lx)
{
	while (lx->input[lx->idx])
	{
		if (lx->state == LEXER_NORMAL)
			process_lx_normal(data, lx);
		else if (lx->state == LEXER_SINGLE_QUOTE)
			process_lx_single_q(data, lx);
		else if (lx->state == LEXER_DOUBLE_QUOTE)
			process_lx_double_q(data, lx);
		(lx->idx)++;
	}
}

t_token	*lexer(t_data *data)
{
	t_lexer	lx;

	init_lexer(&lx);
	lx.input = data->line;
	tokenize_input(data, &lx);

	free(lx.buffer);
	lx.buffer = NULL;

	return (lx.head);
}
