/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:25:07 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 15:40:39 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"

void	reset_data(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->pipeline = NULL;
	data->exit_status = 0;
}

void	init_data(t_data *data, char **envp)
{
	data->line = NULL;
	data->tokens = NULL;
	data->pipeline = NULL;
	data->env = NULL;
	data->exit_status = 0;
	envp_to_env(data, envp);
}
