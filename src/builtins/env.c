/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 14:36:34 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 23:36:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "parser/parser.h"

void	process_env(t_data *data, t_cmd *cmd)
{
	t_env	*node;

	(void)cmd;
	node = data->env;
	while (node)
	{
		if(node->value)
			ft_printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
