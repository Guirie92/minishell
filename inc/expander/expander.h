/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 18:13:55 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 13:29:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

size_t	validate_env_key(unsigned char c);

size_t	get_key_len(char **line, char **str);
void	calculate_env_len(t_data *data, char **line, size_t *len);
size_t	calculate_token_len(t_data *data, char *src);
size_t	calculate_expanded_len(t_data *data, char *line, int *b_has_expanded);

void	fill_expanded_line(t_data *data, char *line, char *expanded_line);
void	fill_env_key(t_data *data, char **src, char **dst);
void	process_token_string(t_data *data, char *src, char *dst);
void	resolve_tokens(t_data *data);

#endif /* EXPANDER_H */