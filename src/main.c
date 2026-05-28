/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/28 12:19:34 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> // del
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	init_data(t_data *data, t_prompt *prompt)
{
	data->line = NULL;
	prompt->buffer[0] = '\0';
	prompt->len = 0;
	prompt->max_len = 2048;
}

int	main(void)
{
	t_data		data;
	t_prompt	prompt;

	init_data(&data, &prompt);
	generate_prompt(&prompt);
	while (1)
	{
		data.line = readline(CLR_LIGHT_BLUE
				"\nminishell\n" CLR_LIGHT_PURPLE "❯ " CLR_RESET);

		printf("line processed\n"); // del
		free(data.line);
	}
	return (0);
}
