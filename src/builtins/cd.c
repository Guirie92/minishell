/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:54:30 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 23:21:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"
#include "builtins/builtins.h"

// static void	cd_home(t_data *data)
// {
// 	const char	*home = getenv("HOME");
// 	t_env		*pwd;
// 	t_env		*oldpwd;

// 	if (!home)
// 		return ;
// 	if (chdir(home) == -1)
// 	{
// 		print_sys_error();
// 		return ;
// 	}
// 	pwd = find_env(data, "PWD");
// 	if (!pwd)
// 		return ;
// 	oldpwd = find_env(data, "OLDPWD");
// 	if (!oldpwd)
// 		return ;
// 	update_env_val(data, oldpwd, pwd->value);
// 	update_env_val(data, pwd, home);
// }

static t_env *create_pwd(t_data *data, char *key, char *value)
{
	char	*full_env;
	size_t	key_len;
	size_t	val_len;
	size_t	full_len;

	if (!key)
		return (NULL);
	if (!value)
	{
		export_single_arg(data, key);
		return (find_env(data, key));
	}
	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	full_len = key_len + val_len + 2;
	full_env = malloc(full_len * sizeof(char));
	if (!full_env)	
		exit_with_error(data);
	ft_strlcpy(full_env, key, full_len);
	ft_strlcat(full_env, "=", full_len);
	ft_strlcat(full_env, value, full_len);
	export_single_arg(data, full_env);
	free(full_env);
	return (find_env(data, key));
}

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
		oldpwd = create_pwd(data, "OLDPWD", NULL);
	if (!pwd || !pwd->value)
		update_env_val(data, oldpwd, NULL);
	else
		update_env_val(data, oldpwd, pwd->value);
	if (!pwd)
	{
		pwd = create_pwd(data, "PWD", cwd);
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
		data->exit_status = 1;
		return ;
	}
	update_cd_envs(data);
}
