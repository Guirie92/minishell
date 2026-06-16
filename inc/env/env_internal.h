/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:30:43 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 13:37:39 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H

# include <stddef.h>

typedef struct s_data	t_data;
 
void	fill_envp(t_data *data, char **envp, size_t size);

#endif /* ENV_INTERNAL_H */