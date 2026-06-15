/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 22:47:44 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"
#include "prompt/prompt.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_control_d(t_data *data)
{
	write(1, "exit\n", 5);
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

static void	shell_loop(t_data *data)
{
	while (1)
	{
		generate_prompt(data->prompt);
		
		data->line = readline(data->prompt->buffer);
		
		check_sigint(data);
		if (!data->line)
			handle_null_line(data);
		if (data->line[0] != '\0')
		{
			add_history(data->line);
			process_input(data);
		}
		
		debug_and_log(data); // delete

		reset_command_state(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_prompt	prompt;

	(void)argc;
	(void)argv;

	data.prompt = &prompt;
	init_data(&data, envp);
	init_signals();

	shell_loop(&data);

	return (0);
}
