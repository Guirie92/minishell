/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:30:12 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 14:37:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

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

void	fill_envp(t_data *data, char **envp, size_t size)
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
