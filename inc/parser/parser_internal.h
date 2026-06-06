/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:51:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 18:17:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser/parser.h"

t_cmd	*init_cmd(t_data *data);
void	add_arg(t_data *data, t_cmd *cmd, const char *s);
void	heredoc_collector(t_data *data);

#endif /* PARSER_INTERNAL_H */