/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 18:13:55 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 21:02:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

size_t	validate_env_key(unsigned char c);
size_t	get_key_len(char **line, char **str);
void	calc_env_from_d_sign(t_data *data, char **line, size_t *len);
size_t	calculate_expanded_len(t_data *data, char *line, int *b_has_expanded);
void	fill_expanded_line(t_data *data, char *line, char *expanded_line);

void	expand_env(t_data *data);

#endif /* EXPANDER_H */