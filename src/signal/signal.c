/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:16:38 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/09 12:09:09 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"
#include "prompt/prompt.h"
#include "ft_printf.h"
#include <readline/readline.h>

volatile sig_atomic_t	g_exit_status;

// static void	sigint_handler(int sig)
// {
// 	t_prompt	prompt;

// 	(void)sig;
// 	write(1, "\n", 1);
// 	init_prompt(&prompt);
// 	generate_prompt(&prompt);
// 	ft_dprintf(STDOUT_FILENO, CLR_PURPLE TEXT_BOLD "\n> "
// 		TEXT_UNBOLD CLR_RESET);
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_exit_status = 130;
// }

static void sigint_handler(int sig)
{
	(void)sig;

	g_exit_status = 130;

	write(1, "\n", 1);

	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


// static void	check_sig_status(int status)
// {
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		g_exit_status = S_SIGINT;	
// 		write(1, "\n", 1); 
// 	}
// 	else
// 		g_exit_status = S_DEFAULT;
// }

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(int status)
{
	(void)status;
	init_signals();
	//check_sig_status(status);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

// ------------------------------------------------- //

// static void	sigint_handler(int sig)
// {
// 	t_prompt	prompt;

// 	(void)sig;
// 	if (g_exit_status == S_DEFAULT || g_exit_status == S_SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		init_prompt(&prompt);
// 		generate_prompt(&prompt);
// 		ft_dprintf(STDOUT_FILENO, CLR_PURPLE TEXT_BOLD "\n> "
// 			TEXT_UNBOLD CLR_RESET);
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_exit_status = S_SIGINT;
// 	}
// 	else if (g_exit_status == S_HD)
// 		g_exit_status = S_SIGINT;
// }

// static void	check_sig_status(int status)
// {
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		g_exit_status = S_SIGINT;	
// 		write(1, "\n", 1); 
// 	}
// 	else
// 		g_exit_status = S_DEFAULT;
// }

// void	init_signals(void)
// {
// 	g_exit_status = S_DEFAULT;
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	reset_signals(int status)
// {
// 	init_signals();
// 	check_sig_status(status);
// }
