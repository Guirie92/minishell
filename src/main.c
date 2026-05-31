/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 14:31:00 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"
#include "lexer/lexer.h"
#include "prompt/prompt.h"
#include <unistd.h>
#include <stdio.h> // del
#include <readline/readline.h>
#include <readline/history.h>

static void	parse_and_execute(t_data *data)
{
	lexer(data);

	//TODO:
	// parser(tokens)
	// expander(parsed_cmds)
	// executor(parsed_cmds)
}

static void	handle_control_d(t_data *data)
{
	write(1, "exit\n", 5);
	clear_data(data);
	exit(EXIT_SUCCESS);
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

		data.line = readline(" ");
		if (!data.line)
			handle_control_d(&data);

		parse_and_execute(&data);

		//generate_prompt(&prompt);
		printf("line processed:\n%s\n", data.line); // del
		//rl_on_new_line();
		//free(data.line);
		clear_data(&data);
	}
	return (0);
}
