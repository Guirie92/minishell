/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:35:53 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 13:24:08 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "clear_resources/clear_resources_internal.h"

static void	free_tokens(t_data *data)
{
	t_token	*tmp;

	while (data->tokens)
	{
		tmp = data->tokens->next;
		free(data->tokens->value);
		free(data->tokens);
		data->tokens = tmp;
	}
	data->tokens = NULL;
}

void	free_env(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		tmp = data->env->next;
		free(data->env->key);
		free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
	data->env = NULL;
}

void	clear_data(t_data *data)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	data->line = NULL;
	free_tokens(data);
	free_pipeline(data);
	free_env(data);
	reset_data(data);

	// TODO: needs to clean up t_env env too
}

void	reset_command_state(t_data *data)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	data->line = NULL;
	free_tokens(data);
	free_pipeline(data);
	reset_data(data);
}
