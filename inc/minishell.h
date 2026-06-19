/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:56:23 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 17:44:47 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "clear_resources/clear_resources.h"
# include "error/error.h"
# include <stddef.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>

# define BUFFER_SIZE 2048

# define CLR_GREEN  "\001\033[32m\002"
# define CLR_BLUE   "\001\033[34m\002"
# define CLR_YELLOW "\001\033[33m\002"
# define CLR_CYAN   "\001\033[36m\002"
# define CLR_GREY   "\001\033[90m\002"
# define CLR_PURPLE "\001\033[35m\002"
# define CLR_RESET  "\001\033[0m\002"
# define CLR_RST    "\033[0m"

# define CLR_LIGHT_PURPLE "\001\033[38;2;195;121;202m\002"
# define CLR_LIGHT_BLUE   "\001\033[38;2;98;152;230m\002"
# define CLR_LIGHT_GREY   "\001\033[38;2;156;156;156m\002"

# define TEXT_BOLD   "\001\033[1m\002"
# define TEXT_UNBOLD "\001\033[22m\002"

extern volatile sig_atomic_t	g_signal;
typedef struct s_pipeline		t_pipeline;
typedef struct s_token			t_token;
typedef struct s_prompt			t_prompt;
typedef struct s_env			t_env;
typedef struct s_builtins		t_builtins;

typedef struct s_data
{
	char		*line;
	t_token		*tokens;
	t_pipeline	*pipeline;
	t_prompt	*prompt;
	t_env		*env;
	t_builtins	*builtins;
	size_t		exit_status;
}	t_data;

typedef enum e_retcode
{
	E_SUCCESS = 0,
	E_FAILURE = 1
}	t_retcode;

/* shell_core.c */
void	process_input(t_data *data);

/* signal.c */
void	sigint_handler(int sig);
void	init_signals(void);
void	update_exit_status(t_data *data, int status);
void	check_sigint(t_data *data);

/* DELETE */
void	debug_and_log(t_data *data);

#endif /* MINISHELL_H */