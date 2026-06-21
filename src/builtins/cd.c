/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:54:30 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 18:01:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"

static void	cd_home(t_data *data)
{
	const char	*home = getenv("HOME");
	t_env		*pwd;
	t_env		*oldpwd;

	if (!home)
		return ;
	if (chdir(home) == -1)
	{
		print_sys_error();
		return ;
	}
	pwd = find_env(data, "PWD");
	if (!pwd)
		return ;
	oldpwd = find_env(data, "OLDPWD");
	if (!oldpwd)
		return ;
	update_env_val(data, oldpwd, pwd->value);
	update_env_val(data, pwd, home);
}

void	process_cd(t_data *data, t_cmd *cmd)
{
	t_env		*pwd;
	t_env		*oldpwd;
	char		*cwd;

	if (!cmd->argv[1])
	{
		cd_home(data);
		return ;
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		print_sys_error();
		return ;
	}
	pwd = find_env(data, "PWD");
	if (!pwd)
		return ;
	oldpwd = find_env(data, "OLDPWD");
	if (!oldpwd)
		return ;
	update_env_val(data, oldpwd, pwd->value);
	cwd = get_current_cwd();
	if (!cwd)
		exit_with_error(data);
	take_env_val(pwd, cwd);
}
