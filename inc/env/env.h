/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:14:24 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 16:26:14 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_data	t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	free_envp(char **envp);
t_env	*find_env(t_data *data, char *entry, size_t len);
void	envp_to_env(t_data *data, char **envp);
char	**env_to_envp(t_data *data);

#endif /* ENV_H */