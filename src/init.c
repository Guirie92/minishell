/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:25:07 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/09 13:53:57 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt/prompt.h"

void	reset_data(t_data *data)
{
	data->line = NULL;
	data->tokens_head = NULL;
	data->pipeline = NULL;
	data->exit_status = 0;
}

void	init_data(t_data *data)
{
	reset_data(data);
	init_prompt(data->prompt);
}
