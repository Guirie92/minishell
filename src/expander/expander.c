/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 13:31:31 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "expander/expander.h"

/*
 * It calculates the expansion in a heredoc line, one at a time
 * (doesn't need quote context)
 */
size_t	calculate_expanded_len(t_data *data, char *line, int *b_has_expanded)
{
	size_t	len;

	len = 0;
	while (*line)
	{
		if (*line == '$')
		{
			*b_has_expanded = 1;
			calculate_env_len(data, &line, &len);
		}
		else
		{
			line++;
			len++;
		}
	}
	return (len);
}

/*
 * It expands the heredoc line, one at a time (doesn't need quote context)
 */
void	fill_expanded_line(t_data *data, char *line, char *expanded_line)
{
	char	*src;
	char	*dst;

	src = line;
	dst = expanded_line;
	while (*src)
	{
		if (*src == '$')
			fill_env_key(data, &src, &dst);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

/*
 * It performs 2 steps: it expands env variables and strip quotes
 * 
 * - It calculates the new len, taking into account (1) quote removal
 *   and (2) expansion (env key into env value)
 * 
 * - allocates the new length
 * 
 * - and writes directly into the new buffer, without quotes, and with env
 *   values expanded
 */
#include <stdio.h>
#include "libft.h"
void	resolve_tokens(t_data *data)
{
	t_token	*token;
	char	*dst;
	size_t	len;

	token = data->tokens;
	while (token)
	{
		if (token->type != TOKEN_WORD)
		{
			token = token->next;
			continue ;
		}
		len = calculate_token_len(data, token->value);

		// ---- DEBUG ---- // 
		printf("WORD (n: %ld | e: %ld)\n", ft_strlen(token->value), len);
		fflush(stdout);
		// ---- DEBUG ---- // 

		dst = malloc((len + 1) * sizeof(char));
		if (!dst)
			exit_with_error(data);
		process_token_string(data, token->value, dst);

		// ---- DEBUG ---- // 
		printf("tok val: %s\n", token->value);
		printf("exp val: %s\n\n", dst);
		fflush(stdout);
		// ---- DEBUG ---- // 
		
		free(token->value);
		token->value = dst;
		token = token->next;
	}
}
