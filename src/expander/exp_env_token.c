/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:40:07 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/22 00:09:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "expander/expander.h"

static void	process_state_normal(t_data *data, char **s, char **dst,
	t_quote_states *state)
{
	if (**s == '$')
	{
		fill_env_key(data, s, dst);
		return ;
	}
	if (**s == '\'')
		*state = QUOTE_CONTEXT_SINGLE;
	else if (**s == '"')
		*state = QUOTE_CONTEXT_DOUBLE;
	else
		*(*dst)++ = **s;
	(*s)++;
}

static void	process_state_single_q(char **s, char **dst, t_quote_states *state)
{
	if (**s == '\'')
		*state = QUOTE_CONTEXT_NORMAL;
	else
		*(*dst)++ = **s;
	(*s)++;
}

static void	process_state_double_q(t_data *data, char **s, char **dst,
	t_quote_states *state)
{
	if (**s == '$')
	{
		fill_env_key(data, s, dst);
		return ;
	}
	if (**s == '"')
		*state = QUOTE_CONTEXT_NORMAL;
	else
		*(*dst)++ = **s;
	(*s)++;
}

void	process_token_string(t_data *data, char *src, char *dst)
{
	t_quote_states	state;

	state = QUOTE_CONTEXT_NORMAL;
	while (*src)
	{
		if (state == QUOTE_CONTEXT_NORMAL)
			process_state_normal(data, &src, &dst, &state);
		else if (state == QUOTE_CONTEXT_SINGLE)
			process_state_single_q(&src, &dst, &state);
		else if (state == QUOTE_CONTEXT_DOUBLE)
			process_state_double_q(data, &src, &dst, &state);
	}
	*dst = '\0';
}
