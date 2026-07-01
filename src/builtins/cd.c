/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:54:30 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 13:55:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"
#include "builtins/builtins.h"

static void	update_cd_envs(t_data *data)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*cwd;

	cwd = get_current_cwd();
	if (!cwd)
		exit_with_error(data);
	pwd = find_env(data, "PWD");
	oldpwd = find_env(data, "OLDPWD");
	if (!oldpwd)
		oldpwd = create_env_key_val(data, "OLDPWD", NULL);
	if (!pwd || !pwd->value)
		update_env_val(data, oldpwd, NULL);
	else
		update_env_val(data, oldpwd, pwd->value);
	if (!pwd)
	{
		pwd = create_env_key_val(data, "PWD", cwd);
		free(cwd);
		return ;
	}
	take_env_val(pwd, cwd);
}

static void	cd_home(t_data *data)
{
	t_env	*home_node;

	home_node = find_env(data, "HOME");
	if (!home_node || !home_node->value)
	{
		print_error_arg(ERR_HOME_UNSET, "cd");
		data->exit_status = 1;
		return ;
	}
	if (chdir(home_node->value) == -1)
	{
		print_sys_error();
		data->exit_status = 1;
		return ;
	}
	update_cd_envs(data);
}

void	process_cd(t_data *data, t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		cd_home(data);
		return ;
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		print_sys_error();
		data->exit_status = 1;
		return ;
	}
	update_cd_envs(data);
}
