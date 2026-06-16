/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:26:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 14:51:11 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"

#include <stdio.h>
void	execute(t_data *data)
{
	t_cmd	*cmd;
	char	**envp;

	cmd = data->pipeline->cmds;
	envp = env_to_envp(data);
	
	// DEBUG
	int i = 0;
	printf("\n---- ENV_TO_ENVP ----\n");
	if (envp)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	// DEBUG END
	
	if (ft_strchr(cmd->argv[0], '/'))
	{
		execve(cmd->argv[0], cmd->argv, envp);
	}
	else
	{
		//execve()
	}
}
