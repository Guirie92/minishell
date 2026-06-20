/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:54:30 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 22:30:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"
#include "env/env.h"

/*
 * In the manual:
 * https://man7.org/linux/man-pages/man3/getcwd.3.html
 * 
 * In the 3rd paragraph, it says:
 * 
 *   "As an extension to the POSIX.1-2001 standard, glibc's getcwd()
 *   allocates the buffer dynamically using malloc(3) if buf is NULL."
 * 
 * This is perfect, because we don't know the length of the current dir, so
 * we let it allocate whatever's necessary and pass it to the PWD env node.
 */
static char	*get_current_cwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_with_error(data);
	return (cwd);
}

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
	cwd = get_current_cwd(data);
	take_env_val(pwd, cwd);
}
