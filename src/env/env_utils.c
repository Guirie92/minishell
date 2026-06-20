/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:30:12 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 23:10:46 by guillsan         ###   ########.fr       */
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
	int		equal_pos;

	node = malloc(sizeof(*node));
	if (!node)
		exit_with_error(data);
	equal_pos = ft_strchr_pos(entry, '=');
	if (equal_pos != -1)
	{
		node->key = ft_strndup(entry, equal_pos);
		if (!node->key)
			exit_with_error(data);
		node->value = ft_strdup(&entry[equal_pos + 1]);
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

void	take_env_val(t_env *env, char *alloc_val)
{
	if (env->value)
		free(env->value);
	env->value = alloc_val;
}
