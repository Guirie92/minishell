/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_resources.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:35:16 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 13:18:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_RESOURCES_H
# define CLEAR_RESOURCES_H

typedef struct s_data	t_data;

void	reset_data(t_data *data);
void	clear_data(t_data *data);
void	reset_command_state(t_data *data);

#endif /* CLEAR_RESOURCES_H */