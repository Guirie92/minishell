/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:45:17 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 20:54:50 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "builtins/builtins.h"

void	builtins_init(t_data *data)
{
	const char				*names[BUILTIN_COUNT] = {
		BUILTIN_N1, BUILTIN_N2, BUILTIN_N3, BUILTIN_N4, BUILTIN_N5,
		BUILTIN_N6, BUILTIN_N7
	};
	const t_builtin_func	funcs[BUILTIN_COUNT] = {
		BUILTIN_F1, BUILTIN_F2, BUILTIN_F3, BUILTIN_F4,
		BUILTIN_F5, BUILTIN_F6, BUILTIN_F7
	};
	size_t					i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		data->builtins[i].name = names[i];
		data->builtins[i].func = funcs[i];
		data->builtins[i].len = ft_strlen(names[i]);
		i++;
	}
}

int		is_builtin(t_data *data, char *cmd)
{
	size_t	len;
	int		i;

	len = ft_strlen(cmd);
	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (len == data->builtins[i].len
			&& ft_strcmp(cmd, data->builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	process_builtin(t_data *data, t_cmd *cmd)
{
	size_t	len;
	int		i;

	len = ft_strlen(cmd->argv[0]);
	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (len == data->builtins[i].len
			&& ft_strcmp(cmd->argv[0], data->builtins[i].name) == 0)
		{
			data->builtins[i].func(data, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

void	process_pwd(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
}

void	process_export(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
}

void	process_unset(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
}

void	process_env(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
}
