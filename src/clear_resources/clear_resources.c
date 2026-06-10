/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:35:53 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/10 17:02:21 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "clear_resources/clear_resources_internal.h"

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
	if (data->line)
		free(data->line);
	data->line = NULL;
	free_tokens(data);
	free_pipeline(data);
	reset_data(data);

	// TODO: needs to clean up t_env env too
}

void	reset_command_state(t_data *data)
{
	// TODO: this is basically "clear_data" as is rn (without env)
	(void)data;
}
