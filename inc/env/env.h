/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:14:24 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 16:15:37 by guillsan         ###   ########.fr       */
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

/* env_alpha.c */
void	print_env_alpha_order(t_data *data);

/* env_utils.c */
t_env	*find_env_len(t_data *data, char *entry, size_t len);
t_env	*create_env_node(t_data *data, char *entry);
void	take_env_val(t_env *env, char *alloc_val);

/* env_funcs.c */
t_env	*find_env(t_data *data, char *entry);
void	update_env_val(t_data *data, t_env *env, const char *new_val);
void	add_env_entry(t_data *data, t_env *env);
void	remove_env_entry(t_data *data, char *entry);

/* env.c */
void	free_envp(char **envp);
void	envp_to_env(t_data *data, char **envp);
char	**env_to_envp(t_data *data);

#endif /* ENV_H */