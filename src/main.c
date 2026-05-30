/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 15:08:09 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "prompt/prompt.h"
#include <stdio.h> // del
#include <readline/readline.h>
#include <readline/history.h>

static void	init_data(t_data *data, t_prompt *prompt)
{
	data->line = NULL;
	init_prompt(prompt);
}

static void	parse_and_execute(t_data *data)
{
	t_token	*head;
	
	head = lexer(data->line);
	(void)head;
}

int	main(void)
{
	t_data		data;
	t_prompt	prompt;

	init_data(&data, &prompt);
	while (1)
	{
		generate_prompt(&prompt);

		data.line = readline(" ");

		parse_and_execute(&data);

		//generate_prompt(&prompt);
		printf("line processed:\n%s\n", data.line); // del
		//rl_on_new_line();
		free(data.line);
	}
	return (0);
}
