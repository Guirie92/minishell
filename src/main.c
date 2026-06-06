/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/06 23:24:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"
#include "prompt/prompt.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

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

int	main(void)
{
	t_data		data;
	t_prompt	prompt;

	data.prompt = &prompt;
	init_data(&data);
	while (1)
	{
		generate_prompt(&prompt);

		data.line = readline(CLR_PURPLE TEXT_BOLD "\n> " TEXT_UNBOLD CLR_RESET);
		
		if (!data.line)
			handle_null_line(&data);
		if (data.line[0] != '\0')
		{
			add_history(data.line);
			process_input(&data);
		}


		debug_and_log(&data);
		
		clear_data(&data);
	}
	return (0);
}
