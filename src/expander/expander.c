/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 20:30:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"

void	expand_env(t_data *data)
{
	t_token	*token;
	char	*src;
	char	*dst;

	token = data->tokens;
	while (token)
	{
		src = token->value;
		calculate_token_len(data, src);
		
		
	}
}


void	calculate_token_len(t_data *data, char *src)
{
	t_quote_states	state;
	size_t			len;

	len = 0;
	state = QUOTE_CONTEXT_NORMAL;
	while (*src)
	{
		if (state == QUOTE_CONTEXT_NORMAL)
			process_state_normal(&src, &len, &state);
		else if (state == QUOTE_CONTEXT_SINGLE)
			process_state_single_q(&src, &len, &state);
		else if (state == QUOTE_CONTEXT_DOUBLE)
			process_state_double_q(&src, &len, &state);
		src++;
	}
}

static void	process_state_normal(char *s, size_t *len, t_quote_states *state)
{
	if (*s == '\'')
	{
		*state = QUOTE_CONTEXT_SINGLE;
		(*len)++;
	}
	else if (*s == '"')
	{
		*state = QUOTE_CONTEXT_DOUBLE;
		(*len)++;
	}
	else if ()
	{
		
	}
	else
	{
		
	}
}

static void	process_state_single_q(char *s, size_t *len, t_quote_states *state)
{
	if (*s == '\'')
		*state = QUOTE_CONTEXT_NORMAL;
	(*len)++;
}

static void	process_state_double_q(char *s, size_t *len, t_quote_states *state)
{
	if (*s == '"')
		*state = QUOTE_CONTEXT_NORMAL;
	else
	{
		
	}
}