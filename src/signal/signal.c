/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:16:38 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 15:30:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt/prompt.h"
#include "ft_printf.h"
#include <readline/readline.h>

int	g_signal;

static void	sigint_handler(int sig)
{
	t_prompt	prompt;

	(void)sig;
	if (g_signal == S_DEFAULT || g_signal == S_SIGINT)
	{
		write(1, "\n", 1);
		init_prompt(&prompt);
		generate_prompt(&prompt);
		ft_dprintf(STDOUT_FILENO, CLR_PURPLE TEXT_BOLD "\n> "
			TEXT_UNBOLD CLR_RESET);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == S_DEFAULT || g_signal == S_HD)
	{
		// TODO
		g_signal = S_SIGINT;
	}
}

void	init_signals(void)
{
	g_signal = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
