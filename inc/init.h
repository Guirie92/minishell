/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:25:52 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 19:45:05 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_data	t_data;
typedef struct s_prompt	t_prompt;

void	init_data(t_data *data);
void	init_prompt(t_prompt *prompt);

#endif /* INIT_H */