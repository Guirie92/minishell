/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 22:32:23 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 23:04:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

t_env	*find_env(t_data *data, char *entry)
{
	t_env	*node;
	size_t	entry_len;

	node = data->env;
	entry_len = ft_strlen(entry);
	while (node)
	{
		if (ft_strlen(node->key) == entry_len
			&& ft_strncmp(node->key, entry, entry_len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	update_env_val(t_data *data, t_env *env, const char *new_val)
{
	size_t	len;

	len = ft_strlen(new_val);
	if (env->value)
		free(env->value);
	env->value = malloc((len + 1) * sizeof(char));
	if (!env->value)
		exit_with_error(data);
	ft_strlcpy(env->value, new_val, len + 1);
}

void	add_env_entry(t_data *data, t_env *env)
{
	t_env	*tail;

	if (!data->env)
	{
		data->env = env;
		return ;
	}
	tail = data->env;
	while (tail && !tail->next)
		tail = tail->next;		
	tail->next = env;
	env->next = NULL;
}

/*
 * Edge case to bear in mind:
 * - Removing the head (first or single element) --> prev == NULL
 */
void	remove_env_entry(t_data *data, char *entry)
{
	t_env	*env;
	t_env	*node;
	t_env	*prev;

	env = find_env(data, entry);
	if (!env)
		return ;
	node = data->env;
	prev = NULL;
	while (node)
	{
		if (node == env)
		{
			if (prev == NULL)
				data->env = node->next;
			else
				prev->next = node->next;
			free(env->key);
			free(env->value);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}
