/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:35:53 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 13:00:57 by guillsan         ###   ########.fr       */
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

	if (data->tokens_head)
	{
		while (data->tokens_head)
		{
			tmp = data->tokens_head->next;
			free(data->tokens_head->value);
			free(data->tokens_head);
			data->tokens_head = tmp;
		}
	}
	data->tokens_head = NULL;
}

void	clear_data(t_data *data)
{
	t_token	*tmp;

	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->tokens_head)
	{
		while (data->tokens_head)
		{
			tmp = data->tokens_head->next;
			free(data->tokens_head->value);
			free(data->tokens_head);
			data->tokens_head = tmp;
		}
	}
	data->tokens_head = NULL;
}
