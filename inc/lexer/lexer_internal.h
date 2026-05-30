/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:50:02 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 16:14:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

#include "lexer/lexer.h"

void	process_lx_normal(t_lexer *lx);
void	process_lx_single_q(t_lexer *lx);
void	process_lx_double_q(t_lexer *lx);

#endif /* LEXER_INTERNAL_H */