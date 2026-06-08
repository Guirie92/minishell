/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:35:53 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 19:45:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "clear_resources/clear_resources_internal.h"

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
	if (data->line)
		free(data->line);
	data->line = NULL;
	free_tokens(data);
	free_pipeline(data);
	reset_data(data);
}
