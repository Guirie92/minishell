/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:11:04 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/18 11:29:50 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "parser/parser.h"
#include "clear_resources/clear_resources.h"

static void	free_path_exit(t_data *data, char **str_arr)
{
	if (str_arr)
		free_str_arr(str_arr);
	exit_with_error(data);
}

/* The ft_strlen + 2 is:
 * 1 for '/' to join the dir and the command, and
 * 1 for the null terminator
 */
static char	*path_join(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	len;

	if (!dir || !cmd)
		return (NULL);
	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len * sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

static char	*search_in_path(t_data *data, char *path_res, char *cmd_name)
{
	char	**path_list;
	char	*full_path;
	size_t	i;

	path_list = ft_split(path_res, ':');
	if (!path_list)
		exit_with_error(data);
	i = 0;
	while (path_list[i])
	{
		full_path = path_join(path_list[i], cmd_name);
		if (!full_path)
			free_path_exit(data, path_list);
		if (access(full_path, X_OK) == 0)
		{
			free_str_arr(path_list);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_arr(path_list);
	return (NULL);
}

void	set_path(t_data *data, t_cmd *cmd)
{
	t_env	*path_res;

	if (!cmd->argv)
	{
		cmd->path = NULL;
		return ;
	}
	if (ft_strchr(cmd->argv[0], '/'))
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		if (!cmd->path)
			exit_with_error(data);
		return ;
	}
	path_res = find_env(data, "PATH", 4);
	if (!path_res || !path_res->value)
	{
		cmd->path = NULL;
		return ;
	}
	cmd->path = search_in_path(data, path_res->value, cmd->argv[0]);
}
