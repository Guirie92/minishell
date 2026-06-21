/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 23:14:20 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 17:26:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "parser/parser.h"

void	process_unset(t_data *data, t_cmd *cmd)
{
	int		i;

	if (!cmd->argv[1])
		return ;
	i = 1;
	while (cmd->argv[i])
	{
		remove_env_entry(data, cmd->argv[i]);
		i++;
	}
}
