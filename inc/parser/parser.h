/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:48:17 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/05 16:06:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd		*cmds;
}	t_pipeline;

void	parser(t_data *data);

#endif /* PARSER_H */