/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:27:21 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 12:58:09 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "minishell.h"

typedef enum e_heredoc_status
{
	HD_SUCCESS,
	HD_EOF,
	HD_FAILURE
}	t_heredoc_status;

void	build_hd_prompt(t_builder *sb, int heredoc_idx);
void	heredoc_exit(t_data *data, int fd[2], t_heredoc_status retcode);
int		check_hd_exit_status(t_data *data, int status);

#endif /* EXECUTOR_INTERNAL_H */