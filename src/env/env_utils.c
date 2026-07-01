/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:30:12 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 13:56:59 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

t_env	*find_env_len(t_data *data, char *entry, size_t len)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (ft_strlen(node->key) == len
			&& ft_strncmp(node->key, entry, len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_env	*create_env_node(t_data *data, char *entry)
{
	t_env	*node;
	int		key_len;

	node = malloc(sizeof(*node));
	if (!node)
		exit_with_error(data);
	key_len = ft_strchr_pos(entry, '=');
	if (key_len != -1)
	{
		node->key = ft_strndup(entry, key_len);
		if (!node->key)
			exit_with_error(data);
		node->value = ft_strdup(&entry[key_len + 1]);
		if (!node->value)
			exit_with_error(data);
	}
	else
	{
		node->key = ft_strdup(entry);
		if (!node->key)
			exit_with_error(data);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*create_env_key_val(t_data *data, char *key, char *value)
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

void	take_env_val(t_env *env, char *alloc_val)
{
	if (env->value)
		free(env->value);
	env->value = alloc_val;
}
