/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:09:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 17:38:29 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

static void	create_token(t_data *data, t_lexer *lx)
{
	t_token node;
	(void)lx;
	(void)data;
	(void)node;
	
	//node = 
	if (lx->head == NULL)
	{
		//lx->head = node;
		//lx->tail = node;
	}
	else
	{
		
	}
}

void	process_lx_normal(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
	create_token(data, lx);
	
}

void	process_lx_single_q(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
}

void	process_lx_double_q(t_data *data, t_lexer *lx)
{
	(void)lx;
	(void)data;
}
