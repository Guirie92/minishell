/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:33:38 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 12:31:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define LEXER_OPERATORS "|><"

typedef enum e_quote_states
{
	QUOTE_CONTEXT_NORMAL,
	QUOTE_CONTEXT_SINGLE,
	QUOTE_CONTEXT_DOUBLE,
}	t_quote_states;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char			*input;
	char			*buffer;
	t_token			*head;
	t_token			*tail;
	size_t			input_idx;
	size_t			buf_idx;
	t_quote_states	state;
}	t_lexer;

/* lexer.c */
int	lexer(t_data *data);

#endif /* LEXER_H */