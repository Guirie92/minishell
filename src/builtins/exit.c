/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:55:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 22:46:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

static int	validate_nbr(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (E_FAILURE);
	if (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i]))
		return (E_FAILURE);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (E_FAILURE);
		i++;
	}
	return (E_SUCCESS);
}

/*
 * Only prints when it's a single-command pipeline. This is, if `cmd->next`
 * is null, that means it is being called from the parent and we can print exit.
 */
void	process_exit(t_data *data, t_cmd *cmd)
{
	int	exit_code;

	if (!data->pipeline->cmds->next)
		ft_dprintf(STDOUT_FILENO, "exit\n");
	if (!cmd->argv[1])
	{
		clear_data(data);
		exit(EXIT_SUCCESS);
	}
	if (validate_nbr(cmd->argv[1]) != E_SUCCESS)
	{
		print_error_arg(ERR_EXIT_NUMERIC, "exit");
		clear_data(data);
		exit(2);
	}
	if (cmd->argc > 2)
	{
		print_error_arg(ERR_EXIT_ARGS, "exit");
		if (!data->pipeline->cmds->next)
		{
			data->exit_status = 1;
			return ;
		}
		else
			exit(EXIT_FAILURE);
	}
	exit_code = ft_atoi(cmd->argv[1]);
	clear_data(data);
	exit(exit_code);
}
