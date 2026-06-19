/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:25:07 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 23:21:05 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "builtins/builtins.h"

void	reset_data(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->pipeline = NULL;
	if (data->saved_fd[0] != -1)
		close(data->saved_fd[0]);
	if (data->saved_fd[1] != -1)
		close(data->saved_fd[1]);
	data->saved_fd[0] = -1;
	data->saved_fd[1] = -1;
}

void	init_data(t_data *data, char **envp)
{
	data->line = NULL;
	data->tokens = NULL;
	data->pipeline = NULL;
	data->env = NULL;
	data->exit_status = 0;
	data->saved_fd[0] = -1;
	data->saved_fd[1] = -1;
	data->exit_status = 0;
	envp_to_env(data, envp);
	builtins_init(data);
}
