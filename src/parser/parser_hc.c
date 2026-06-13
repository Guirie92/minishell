/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:30:51 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 17:13:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "lexer/lexer.h"

static void	process_state_normal(char **dst, char *s, t_redir *redir,
				t_quote_states *state);
static void	process_state_single_q(char **dst, char *s, t_quote_states *state);
static void	process_state_double_q(char **dst, char *s, t_quote_states *state);

void	parse_heredoc_delimiter(t_data *data, t_redir *redir, char *delimiter)
{
	t_quote_states	state;
	char			*str;

	state = QUOTE_CONTEXT_NORMAL;
	redir->target = malloc((ft_strlen(delimiter) + 1) * sizeof(char));
	if (!redir->target)
		exit_with_error(data);
	str = redir->target;
	redir->should_expand_hd = 1;
	while (*delimiter)
	{
		if (state == QUOTE_CONTEXT_NORMAL)
			process_state_normal(&str, delimiter, redir, &state);
		else if (state == QUOTE_CONTEXT_SINGLE)
			process_state_single_q(&str, delimiter, &state);
		else if (state == QUOTE_CONTEXT_DOUBLE)
			process_state_double_q(&str, delimiter, &state);
		delimiter++;
	}
	*str = '\0';
}

static void	process_state_normal(char **dst, char *s, t_redir *redir,
	t_quote_states *state)
{
	if (*s == '\'')
	{
		*state = QUOTE_CONTEXT_SINGLE;
		redir->should_expand_hd = 0;
	}
	else if (*s == '"')
	{
		*state = QUOTE_CONTEXT_DOUBLE;
		redir->should_expand_hd = 0;
	}
	else
	{
		**dst = *s;
		(*dst)++;
	}
}

static void	process_state_single_q(char **dst, char *s, t_quote_states *state)
{
	if (*s == '\'')
		*state = QUOTE_CONTEXT_NORMAL;
	else
	{
		**dst = *s;
		(*dst)++;
	}
}

static void	process_state_double_q(char **dst, char *s, t_quote_states *state)
{
	if (*s == '"')
		*state = QUOTE_CONTEXT_NORMAL;
	else
	{
		**dst = *s;
		(*dst)++;
	}
}
