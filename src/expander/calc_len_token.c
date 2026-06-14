/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:39:54 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 13:12:02 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "expander/expander.h"

static void	process_state_normal(t_data *data, char **s, size_t *len,
	t_quote_states *state)
{
	if (**s == '$')
	{
		calculate_env_len(data, s, len);
		return ;
	}
	if (**s == '\'')
		*state = QUOTE_CONTEXT_SINGLE;
	else if (**s == '"')
		*state = QUOTE_CONTEXT_DOUBLE;
	else
		(*len)++;
	(*s)++;
}

static void	process_state_single_q(char **s, size_t *len, t_quote_states *state)
{
	if (**s == '\'')
		*state = QUOTE_CONTEXT_NORMAL;
	else
		(*len)++;
	(*s)++;
}

static void	process_state_double_q(t_data *data, char **s, size_t *len,
	t_quote_states *state)
{
	if (**s == '$')
	{
		calculate_env_len(data, s, len);
		return ;
	}
	if (**s == '"')
		*state = QUOTE_CONTEXT_NORMAL;
	else
		(*len)++;
	(*s)++;
}

size_t	calculate_token_len(t_data *data, char *src)
{
	t_quote_states	state;
	size_t			len;

	len = 0;
	state = QUOTE_CONTEXT_NORMAL;
	while (*src)
	{
		if (state == QUOTE_CONTEXT_NORMAL)
			process_state_normal(data, &src, &len, &state);
		else if (state == QUOTE_CONTEXT_SINGLE)
			process_state_single_q(&src, &len, &state);
		else if (state == QUOTE_CONTEXT_DOUBLE)
			process_state_double_q(data, &src, &len, &state);
	}
	return (len);
}
