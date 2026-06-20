/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:14:03 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 23:11:39 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

void	free_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static void	cleanup_exit(t_data *data, char **envp, size_t count)
{
	size_t	i;

	if (!envp)
		exit_with_error(data);
	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	exit_with_error(data);
}

static void	fill_envp(t_data *data, char **envp, size_t size)
{
	t_env	*env;
	size_t	strlen;
	size_t	i;

	env = data->env;
	i = 0;
	while (env)
	{
		strlen = ft_strlen(env->key) + 1;
		strlen += ft_strlen(env->value);
		envp[i] = malloc((strlen + 1) * sizeof(char));
		if (!envp[i])
			cleanup_exit(data, envp, i);
		ft_strlcpy(envp[i], env->key, strlen + 1);
		ft_strlcat(envp[i], "=", strlen + 1);
		ft_strlcat(envp[i], env->value, strlen + 1);
		env = env->next;
		i++;
	}
	envp[size] = NULL;
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
