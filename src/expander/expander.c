/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 22:48:00 by guillsan         ###   ########.fr       */
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
		calc_env_from_d_sign(data, s, len);
		return ;
	}
	if (**s == '\'')
		*state = QUOTE_CONTEXT_SINGLE;
	else if (**s == '"')
		*state = QUOTE_CONTEXT_DOUBLE;
	(*len)++;
	(*s)++;
}

static void	process_state_single_q(char **s, size_t *len, t_quote_states *state)
{
	if (**s == '\'')
		*state = QUOTE_CONTEXT_NORMAL;
	(*s)++;
	(*len)++;
}

static void	process_state_double_q(t_data *data, char **s, size_t *len,
	t_quote_states *state)
{
	if (**s == '$')
	{
		calc_env_from_d_sign(data, s, len);
		return ;
	}
	if (**s == '"')
		*state = QUOTE_CONTEXT_NORMAL;
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
#include <stdio.h>
#include "libft.h"
void	expand_env(t_data *data)
{
	t_token	*token;
	char	*src;
	//char	*dst;
	size_t	len;

	token = data->tokens;
	while (token)
	{
		src = token->value;
		len = calculate_token_len(data, src);

		char	*token_type;
		if (token->type == TOKEN_WORD)
			token_type = "WORD";
		else if (token->type == TOKEN_PIPE)
			token_type = "PIPE";
		else if (token->type == TOKEN_REDIR_IN)
			token_type = "REDIR_IN";
		else if (token->type == TOKEN_REDIR_OUT)
			token_type = "REDIR_OUT";
		else if (token->type == TOKEN_APPEND)
			token_type = "APPEND";
		else if (token->type == TOKEN_HEREDOC)
			token_type = "HEREDOC";
		if (token->type == TOKEN_WORD)
			printf("%s(n: %ld | e: %ld)\n", token_type, ft_strlen(token->value), len);
		fflush(stdout);

		token = token->next;
	}
}
