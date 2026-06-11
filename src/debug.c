/* DELETE FILE - only for debugging purposes */

#include "minishell.h"
#include "libft.h"
#include "init.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "prompt/prompt.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

#define DEBUG_CODE "minishell_debug"

static int	g_is_debug = 0;

static const char	*get_redir_name(t_redir_type type)
{
    static const char *names[] = {"REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC"};
    return (type >= 0 && type <= 3) ? names[type] : "UNKNOWN";
}

static void	debug_raw_input(t_data *data)
{
	int	i = 0;

	printf(CLR_YELLOW "\n--- RAW INPUT ---\n" CLR_RESET);
	fflush(stdout);
	while (data->line[i])
	{
		write(1, &data->line[i++], 1);
	}
	write(1, "\n", 1);
}

static void	debug_lexer(t_data *data)
{
	t_token	*token;
	char	*token_type;

	token = data->tokens;
	if (!token)
		return ;
	printf(CLR_YELLOW "\n----- LEXER -----\n" CLR_RESET);
	while (token)
	{
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

/*
 * G = GREEN
 * P = PURPLE
 * C = CYAN
 * 
 * V = VERTICAL (│)
 * B = BRANCH   (├)
 * L = LAST     (└)
 * E = EMPTY    ( )
 */
/* GREEN */
#define PREFFIX_GV CLR_GREEN " │   " CLR_RESET
#define PREFFIX_GB CLR_GREEN " ├── " CLR_RESET
#define PREFFIX_GL CLR_GREEN " └── " CLR_RESET
#define PREFFIX_GE CLR_GREEN "     " CLR_RESET

/* PURPLE */
#define PREFFIX_GE_PV PREFFIX_GE CLR_PURPLE " │   " CLR_RESET
#define PREFFIX_GE_PB PREFFIX_GE CLR_PURPLE " ├── " CLR_RESET
#define PREFFIX_GE_PL PREFFIX_GE CLR_PURPLE " └── " CLR_RESET
#define PREFFIX_GE_PE PREFFIX_GE CLR_PURPLE "     " CLR_RESET

#define PREFFIX_GV_PV PREFFIX_GV CLR_PURPLE " │   " CLR_RESET
#define PREFFIX_GV_PB PREFFIX_GV CLR_PURPLE " ├── " CLR_RESET
#define PREFFIX_GV_PL PREFFIX_GV CLR_PURPLE " └── " CLR_RESET
#define PREFFIX_GV_PE PREFFIX_GV CLR_PURPLE "     " CLR_RESET

/* CYAN */
#define PREFFIX_GE_PE_CV PREFFIX_GE_PE CLR_CYAN " │   " CLR_RESET
#define PREFFIX_GE_PE_CB PREFFIX_GE_PE CLR_CYAN " ├── " CLR_RESET
#define PREFFIX_GE_PE_CL PREFFIX_GE_PE CLR_CYAN " └── " CLR_RESET
#define PREFFIX_GE_PE_CE PREFFIX_GE_PE CLR_CYAN "     " CLR_RESET

#define PREFFIX_GE_PV_CV PREFFIX_GE_PV CLR_CYAN " │   " CLR_RESET
#define PREFFIX_GE_PV_CB PREFFIX_GE_PV CLR_CYAN " ├── " CLR_RESET
#define PREFFIX_GE_PV_CL PREFFIX_GE_PV CLR_CYAN " └── " CLR_RESET
#define PREFFIX_GE_PV_CE PREFFIX_GE_PV CLR_CYAN "     " CLR_RESET

#define PREFFIX_GV_PE_CV PREFFIX_GV_PE CLR_CYAN " │   " CLR_RESET
#define PREFFIX_GV_PE_CB PREFFIX_GV_PE CLR_CYAN " ├── " CLR_RESET
#define PREFFIX_GV_PE_CL PREFFIX_GV_PE CLR_CYAN " └── " CLR_RESET
#define PREFFIX_GV_PE_CE PREFFIX_GV_PE CLR_CYAN "     " CLR_RESET

#define PREFFIX_GV_PV_CV PREFFIX_GV_PV CLR_CYAN " │   " CLR_RESET
#define PREFFIX_GV_PV_CB PREFFIX_GV_PV CLR_CYAN " ├── " CLR_RESET
#define PREFFIX_GV_PV_CL PREFFIX_GV_PV CLR_CYAN " └── " CLR_RESET
#define PREFFIX_GV_PV_CE PREFFIX_GV_PV CLR_CYAN "     " CLR_RESET

static void	print_heredoc_content(char *preffix, t_redir *redir)
{
	char	buffer[2048];
	char	line[1024];
	int		line_idx = 0;
	ssize_t	bytes_read;
	int		i;

	while ((bytes_read = read(redir->heredoc_fd, buffer, 2048)) > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
			{
				line[line_idx] = '\0';
				printf("%s", preffix);
				printf("-> %s\n", line);
				// printf("%14s -> %s\n", " ", line);
				line_idx = 0;
			}
			else if (line_idx < (int)sizeof(line) - 1)
				line[line_idx++] = buffer[i];
			i++;
		}
	}
}

static void debug_parser(t_data *data)
{
	t_cmd		*cmd;
	t_redir		*redir;
	t_pipeline	*pipeline;
	int			c_idx = 0;
	int			i;

	pipeline = data->pipeline;
	if (!pipeline || !pipeline->cmds)
		return ;

	printf(CLR_YELLOW "\n----- PARSER ----\n" CLR_RESET);
	cmd = pipeline->cmds;
	while (cmd)
	{
		printf("cmd[%d]\n", c_idx);

		printf(PREFFIX_GB "argv\n");
		i = 0;
		while (i < cmd->argc)
		{
			printf(PREFFIX_GV_PB "argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}

		if (!cmd->next)
		{
			printf(PREFFIX_GL "redir\n");
			redir = cmd->redirs;
			if (!redir)
				printf(PREFFIX_GE_PL "(NULL)\n");
			while (redir)
			{
				if (redir->next)
				{
					printf(PREFFIX_GE_PB "%s: %s\n", get_redir_name(redir->type), redir->target);
					if (redir->type != HEREDOC)
						printf(PREFFIX_GE_PV_CL "(heredoc_fd: %d)\n", redir->heredoc_fd);
					else
					{
						printf(PREFFIX_GE_PV_CB "(heredoc_fd: %d)\n", redir->heredoc_fd);
						printf(PREFFIX_GE_PV_CL "content:\n");
						print_heredoc_content(PREFFIX_GE_PV_CE, redir);
					}
				}
				else
				{
					printf(PREFFIX_GE_PL "%s: %s\n", get_redir_name(redir->type), redir->target);
					if (redir->type != HEREDOC)
						printf(PREFFIX_GE_PE_CL "(heredoc_fd: %d)\n", redir->heredoc_fd);
					else
					{
						printf(PREFFIX_GE_PE_CB "(heredoc_fd: %d)\n", redir->heredoc_fd);
						printf(PREFFIX_GE_PE_CL "content:\n");
						print_heredoc_content(PREFFIX_GE_PE_CE, redir);
					}
				}
				redir = redir->next;
			}
		}
		else
		{
			printf(PREFFIX_GB "redir\n");
			redir = cmd->redirs;
			if (!redir)
				printf(PREFFIX_GV_PL "(NULL)\n");
			while (redir)
			{
				if (!redir->next)
				{
					printf(PREFFIX_GV_PL "%s: %s\n", get_redir_name(redir->type), redir->target);
					if (redir->type != HEREDOC)
						printf(PREFFIX_GV_PE_CL "(heredoc_fd: %d)\n", redir->heredoc_fd);
					else
					{
						printf(PREFFIX_GV_PE_CB "(heredoc_fd: %d)\n", redir->heredoc_fd);
						printf(PREFFIX_GV_PE_CL "content:\n");
						print_heredoc_content(PREFFIX_GV_PE_CE, redir);
					}
				}
				else
				{
					printf(PREFFIX_GV_PB "%s: %s\n", get_redir_name(redir->type), redir->target);
					if (redir->type != HEREDOC)
						printf(PREFFIX_GV_PV_CL "(heredoc_fd: %d)\n", redir->heredoc_fd);
					else
					{
						printf(PREFFIX_GV_PV_CB "(heredoc_fd: %d)\n", redir->heredoc_fd);
						printf(PREFFIX_GV_PV_CL "content:\n");
						print_heredoc_content(PREFFIX_GV_PV_CE, redir);
					}
				}
				redir = redir->next;
			}
		}

		cmd = cmd->next;
		c_idx++;
		if (cmd)
			printf(CLR_GREEN " │\n" CLR_RESET);
	}
	fflush(stdout);
}

void	debug_and_log(t_data *data)
{
	if (ft_strcmp(data->line, DEBUG_CODE) == 0)
		g_is_debug = !g_is_debug;

	if (!g_is_debug)
		return ;

	printf("\ndata->exit_status: %d\n", data->exit_status);

	debug_raw_input(data);
	debug_lexer(data);
	debug_parser(data);
}
