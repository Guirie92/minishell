/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 23:13:46 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 17:03:54 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "parser/parser.h"

static int	is_valid_id(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	process_existing_entry(t_data *data, t_env *env_node, char *arg,
	int key_len)
{
	char	*new_val;

	if (arg[key_len] != '=')
		return ;
	new_val = arg + key_len + 1;
	if (env_node->value && ft_strcmp(env_node->value, new_val) == 0)
		return ;
	if (env_node->value)
		free(env_node->value);
	env_node->value = ft_strdup(new_val);
	if (!env_node->value)
		exit_with_error(data);
}

static void	export_single_arg(t_data *data, char *arg)
{
	int		key_len;
	t_env	*env_node;
	t_env	*new_node;

	key_len = ft_strchr_pos(arg, '=');
	if (key_len == -1)
		key_len = ft_strlen(arg);
	env_node = find_env_len(data, arg, key_len);
	if (!env_node)
	{
		new_node = create_env_node(data, arg);
		add_env_entry(data, new_node);
	}
	else
		process_existing_entry(data, env_node, arg, key_len);
}

static void	loop_argv_export(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_id(argv[i]))
		{
			print_error_arg(ERR_EXPORT_BAD_ID, argv[i]);
			data->exit_status = 1;
		}
		else
			export_single_arg(data, argv[i]);
		i++;
	}
}

void	process_export(t_data *data, t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		print_env_alpha_order(data);
		return ;
	}
	loop_argv_export(data, cmd->argv);
}
