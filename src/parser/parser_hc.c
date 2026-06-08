/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:30:51 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 15:30:13 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "lexer/lexer.h"

static void	process_state_normal(char **dst, char *s, t_lexer_states *state);
static void	process_state_single_q(char **dst, char *s, t_lexer_states *state);
static void	process_state_double_q(char **dst, char *s, t_lexer_states *state);

void	parse_heredoc_delimiter(t_data *data, t_redir *redir, char *delimiter)
{
	t_lexer_states	state;
	char			*str;

	state = LEXER_NORMAL;
	redir->target = malloc((ft_strlen(delimiter) + 1) * sizeof(char));
	if (!redir->target)
		exit_with_error(data);
	str = redir->target;
	while (*delimiter)
	{
		if (state == LEXER_NORMAL)
			process_state_normal(&str, delimiter, &state);
		else if (state == LEXER_SINGLE_QUOTE)
			process_state_single_q(&str, delimiter, &state);
		else if (state == LEXER_DOUBLE_QUOTE)
			process_state_double_q(&str, delimiter, &state);
		delimiter++;
	}
	*str = '\0';
}

static void	process_state_normal(char **dst, char *s, t_lexer_states *state)
{
	if (*s == '\'')
		*state = LEXER_SINGLE_QUOTE;
	else if (*s == '"')
		*state = LEXER_DOUBLE_QUOTE;
	else
	{
		**dst = *s;
		(*dst)++;
	}
}

static void	process_state_single_q(char **dst, char *s, t_lexer_states *state)
{
	if (*s == '\'')
		*state = LEXER_NORMAL;
	else
	{
		**dst = *s;
		(*dst)++;
	}
}

static void	process_state_double_q(char **dst, char *s, t_lexer_states *state)
{
	if (*s == '"')
		*state = LEXER_NORMAL;
	else
	{
		**dst = *s;
		(*dst)++;
	}
}
