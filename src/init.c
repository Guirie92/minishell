/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:25:07 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:44:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt/prompt.h"

void	init_prompt(t_prompt *prompt)
{
	prompt->buffer[0] = '\0';
	prompt->len = 0;
	prompt->max_len = 2048;
}

void	init_data(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	init_prompt(data->prompt);
}
