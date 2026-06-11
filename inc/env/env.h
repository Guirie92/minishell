/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:14:24 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 20:46:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_data	t_data;

void	envp_to_env(t_data *data, char **envp);

#endif /* ENV_H */