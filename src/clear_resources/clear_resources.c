/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:35:53 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:13:26 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"

void	free_line(t_data *data)
{
	free(data->line);
}

void	free_tokens(t_data *data)
{
	t_token	*tmp;

	if (data->tokens)
	{
		while (data->tokens)
		{
			tmp = data->tokens->next;
			free(data->tokens->value);
			free(data->tokens);
			data->tokens = tmp;
		}
	}
	data->tokens = NULL;
}

void	clear_data(t_data *data)
{
	t_token	*tmp;

	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->tokens)
	{
		while (data->tokens)
		{
			tmp = data->tokens->next;
			free(data->tokens->value);
			free(data->tokens);
			data->tokens = tmp;
		}
	}
	data->tokens = NULL;
}
