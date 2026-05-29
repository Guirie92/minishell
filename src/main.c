/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/29 07:32:37 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_builder.h" // del
#include <stdio.h> // del
#include <readline/readline.h>
#include <readline/history.h>

static void	init_data(t_data *data, t_prompt *prompt)
{
	data->line = NULL;
	init_prompt(prompt);
}

int	main(void)
{
	t_data		data;
	t_prompt	prompt;

	init_data(&data, &prompt);

	while (1)
	{
		//data.line = readline("minishell> ");
		//break;

		generate_prompt(&prompt);
		// data.line = readline(CLR_LIGHT_PURPLE "❯ " CLR_RESET);
		data.line = readline(" ");
		//generate_prompt(&prompt);

		printf("line processed\n"); // del
		rl_on_new_line();

		
		free(data.line);
	}
	return (0);
}
