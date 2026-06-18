/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:34:18 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/18 17:33:56 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "string_builder/string_builder.h"
#include "executor/executor_internal.h"

void	hd_exit_status_handler(t_data *data, int status)
{
	update_exit_status(data, status);
	if (data->exit_status == 128 + SIGINT)
		write(1, "\n", 1);
}

void	build_hd_prompt(t_builder *sb, int heredoc_idx)
{
	builder_init(sb);
	builder_append(sb, "heredoc(");
	builder_append_nbr(sb, (int)heredoc_idx);
	builder_append(sb, ")> ");
}

void	heredoc_exit(t_data *data, int fd[2], t_heredoc_status retcode)
{
	close(fd[0]);
	close(fd[1]);
	clear_data(data);
	exit(retcode);
}

int	check_hd_exit_status(t_data *data, int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == HD_FAILURE)
			exit_with_error(data);
		else if (WEXITSTATUS(status) == HD_EOF)
			return (E_FAILURE);
	}
	return (E_SUCCESS);
}
