/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:07:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 14:00:17 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "prompt/prompt.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "expander/expander.h"
#include "executor/executor.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_control_d(t_data *data)
{
	ft_dprintf(STDOUT_FILENO, "exit\n");
	clear_data(data);
	exit(EXIT_SUCCESS);
}

static void	handle_null_line(t_data *data)
{
	if (errno == ENOMEM)
		exit_with_error(data);
	else
		handle_control_d(data);
}

void	shell_loop(t_data *data)
{
	while (1)
	{
		generate_prompt(data, data->prompt);
		data->line = readline(data->prompt->buffer);
		check_sigint(data);
		if (!data->line)
			handle_null_line(data);
		if (data->line[0] != '\0' && !ft_str_isspace(data->line))
		{
			add_history(data->line);
			process_input(data);
		}
		reset_command_state(data);
	}
}

void	process_input(t_data *data)
{
	if (lexer(data) != E_SUCCESS)
		return ;
	if (parser(data) != E_SUCCESS)
		return ;
	if (heredoc_collector(data) != E_SUCCESS)
		return ;
	resolve_pipeline(data);
	execute(data);
}
