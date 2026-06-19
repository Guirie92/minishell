/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:27:21 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 14:19:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "minishell.h"

typedef struct s_builder	t_builder;
typedef struct s_cmd		t_cmd;

typedef enum e_heredoc_status
{
	HD_SUCCESS,
	HD_EOF,
	HD_FAILURE
}	t_heredoc_status;

void	set_path(t_data *data, t_cmd *cmd);

/* redirs */
void	handle_redirs(t_data *data, t_cmd *cmd);
	
/* process_cmd */
void	process_cmd_in_child(t_data *data, t_cmd *cmd, int read_fd,
	int next_pipe[2]);

/* heredoc */
void	build_hd_prompt(t_builder *sb, int heredoc_idx);
void	hd_exit_status_handler(t_data *data, int status);
void	heredoc_exit(t_data *data, int fd[2], t_heredoc_status retcode);
int		check_hd_exit_status(t_data *data, int status);

#endif /* EXECUTOR_INTERNAL_H */