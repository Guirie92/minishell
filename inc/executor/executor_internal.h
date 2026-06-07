/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:27:21 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 17:47:39 by guillsan         ###   ########.fr       */
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

#endif /* EXECUTOR_INTERNAL_H */