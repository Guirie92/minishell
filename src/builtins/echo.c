/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:36:24 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 18:52:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

void	process_echo(t_data *data, t_cmd *cmd)
{
	size_t	i;
	int		b_n;

	i = 1;
	b_n = 0;
	if (ft_strlen(cmd->argv[1]) == 2 && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		b_n = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			ft_printf(" ");
		else if (!b_n)
			ft_printf("\n");
		i++;
	}
}
