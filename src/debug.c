/* DELETE FILE - only for debugging purposes */

#include "minishell.h"
#include "init.h"
#include "lexer/lexer.h"
#include "prompt/prompt.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

static void	debug_lexer(t_data *data)
{
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
			printf("%s(%s)\n", token_type, token->value);
		else
			printf("%s %s\n", token_type, token->value);
		fflush(stdout);
		token = token->next;
	}
}

void	debug_and_log(t_data *data)
{
	debug_lexer(data);
}
