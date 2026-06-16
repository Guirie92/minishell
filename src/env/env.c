/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:14:03 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 14:04:50 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "env/env_internal.h"
#include "libft.h"

t_env	*find_env(t_data *data, char *entry, size_t len)
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

static t_env	*create_env_node(t_data *data, char *entry)
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

void	envp_to_env(t_data *data, char **envp)
{
	t_env	*tail;

	if (!envp || !*envp)
		return ;
	tail = create_env_node(data, *envp);
	data->env = tail;
	envp++;
	while (*envp)
	{
		tail->next = create_env_node(data, *envp);
		tail = tail->next;
		envp++;
	}
}

char	**env_to_envp(t_data *data)
{
	char	**envp;
	t_env	*env;
	size_t	size;

	env = data->env;
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	envp = malloc((size + 1) * sizeof(*envp));
	if (!envp)
		exit_with_error(data);
	fill_envp(data, envp, size);
	return (envp);
}
