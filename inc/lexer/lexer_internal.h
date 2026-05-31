/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:50:02 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 20:47:00 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "lexer/lexer.h"

typedef enum e_token_mode
{
	TOKEN_DEFAULT,
	TOKEN_ALLOW_EMPTY
}	t_token_mode;

void	exit_lexer_with_error(t_data *data, t_lexer *lx);
void	reset_buffer(t_lexer *lx);
void	add_token(t_data *data, t_lexer *lx, t_token_type token_type,
	t_token_mode allow_empty);
void	process_lx_normal(t_data *data, t_lexer *lx);
void	process_lx_single_q(t_data *data, t_lexer *lx);
void	process_lx_double_q(t_data *data, t_lexer *lx);

#endif /* LEXER_INTERNAL_H */