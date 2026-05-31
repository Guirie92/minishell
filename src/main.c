/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 18:27:03 by guillsan         ###   ########.fr       */
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


	// ------- DEL BELOW ------- //

	t_token *token;

	token = data->tokens_head;
	if (token)
		printf("\n");
	while (token)
	{
		char *token_type;
		
		if (token->type == TOKEN_WORD)
			token_type = "WORD";
		else if (token->type == TOKEN_PIPE)
			token_type = "PIPE";
		else if (token->type == TOKEN_REDIR_IN)
			token_type = "REDIR_IN";
		else if (token->type == TOKEN_REDIR_OUT)
			token_type = "REDIR_OUT";
		else if (token->type == TOKEN_APPEND)
			token_type = "APPEND";
		else if (token->type == TOKEN_HEREDOC)
			token_type = "HEREDOC";
		if (token->type == TOKEN_WORD)
			printf("%s(\"%s\")\n", token_type, token->value);
		else
			printf("%s %s\n", token_type, token->value);
		fflush(stdout);
		token = token->next;
	}
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

		//printf("line processed:\n%s\n", data.line); // del
		//rl_on_new_line();
		//free(data.line);
		clear_data(&data);
	}
	return (0);
}
