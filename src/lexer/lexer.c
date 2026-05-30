/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:31:29 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 16:15:29 by guillsan         ###   ########.fr       */
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

static void	cleanup_lexer(t_lexer *lx)
{
	free(lx->buffer);
	lx->buffer = NULL;
}

static void tokenize_input(t_lexer *lx)
{
	while(lx->input[lx->idx])
	{
		if (lx->state == LEXER_NORMAL)
			process_lx_normal(lx);
		else if (lx->state == LEXER_SINGLE_QUOTE)
			process_lx_single_q(lx);
		else if (lx->state == LEXER_DOUBLE_QUOTE)
			process_lx_double_q(lx);
		(lx->idx)++;
	}
}

t_token	*lexer(char *line)
{
	t_lexer lx;

	init_lexer(&lx);
	lx.input = line;
	tokenize_input(&lx);
	
	cleanup_lexer(&lx);

	return (lx.head);
}
