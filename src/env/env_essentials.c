/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_essentials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 13:05:32 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 13:42:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

static void	set_shlvl(t_data *data)
{
	const char	*c_shlvl = "SHLVL=1";
	t_env		*shlvl;
	char		buf[32];
	int			shlvl_int;
	size_t		len;

	ft_memset((void *)buf, 0, sizeof(buf));
	shlvl = find_env(data, "SHLVL");
	if (!shlvl || !shlvl->value)
	{
		export_single_arg(data, (char *)c_shlvl);
		return ;
	}
	shlvl_int = ft_atoi(shlvl->value);
	shlvl_int++;
	ft_strlcpy(buf, "SHLVL=", sizeof(buf));
	len = ft_strlen(buf);
	ft_itoa_buffer(shlvl_int, buf + len, sizeof(buf) - len);
	export_single_arg(data, buf);
}

void	create_oldpwd(t_data *data)
{
	const char	*oldpwd = "OLDPWD";

	export_single_arg(data, (char *)oldpwd);
}

void	create_pwd(t_data *data)
{
	const char	*pwd_key = "PWD=";
	char		*cwd;
	char		*pwd;

	cwd = get_current_cwd();
	if (!cwd)
		exit_with_error(data);
	pwd = ft_strjoin(pwd_key, cwd);
	free(cwd);
	if (!pwd)
		exit_with_error(data);
	export_single_arg(data, pwd);
	free(pwd);
}

void	ensure_essentials_env(t_data *data)
{
	t_env	*oldpwd;
	t_env	*pwd;

	set_shlvl(data);
	oldpwd = find_env(data, "OLDPWD");
	if (!oldpwd)
		create_oldpwd(data);
	pwd = find_env(data, "PWD");
	if (!pwd)
		create_pwd(data);
}
