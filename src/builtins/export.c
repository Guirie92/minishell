/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 23:13:46 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 13:12:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

static void	print_env_alpha_order(t_data *data)
{
	//TODO
	(void)data;
}

void	process_export(t_data *data, t_cmd *cmd)
{
	char	*env_key;
	int		equal_pos;
	int		i;

	if (!cmd->argv[1])
	{
		print_env_alpha_order(data);
		return ;
	}
	i = 1;
	equal_pos = ft_strchr_pos(cmd->argv[1], '=');

	// TODO: validate proper variable name
	
	if (equal_pos != -1)
	{
		//TODO	
	}
}
