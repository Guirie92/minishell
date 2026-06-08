/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:51:50 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 12:01:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser/parser.h"

t_cmd	*init_cmd(t_data *data);
t_redir	*init_redir(t_data *data);
void	add_arg(t_data *data, t_cmd *cmd, const char *s);
void	add_redir(t_data *data, t_cmd *cmd, t_redir *redir, t_token *token);

/* parser_hd.c */
void	parse_heredoc_delimiter(t_data *data, t_redir *redir, char *delimiter);

#endif /* PARSER_INTERNAL_H */