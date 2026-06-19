/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:45:17 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 18:36:21 by guillsan         ###   ########.fr       */
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

void	process_cd(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
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

void	process_exit(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	// TODO
}