/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:16:38 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/09 18:39:21 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"
#include "prompt/prompt.h"
#include "ft_printf.h"
#include <readline/readline.h>

volatile sig_atomic_t	g_signal;

static void	redisplay_prompt()
{
	char	*nl;
	int		i;
	int		idx;
	char	prompt[PROMPT_SIZE];

	idx = 0;
	prompt[idx++] = '\n';
	if (rl_prompt)
	{
		nl = ft_strrchr(rl_prompt, '\n');
		if (nl)
		{
			i = 0;
			while (&rl_prompt[i] <= nl && idx < PROMPT_SIZE - 1)
			{
				if (rl_prompt[i] != '\001' && rl_prompt[i] != '\002')
					prompt[idx++] = rl_prompt[i];
				i++;
			}
		}
	}
	write(STDOUT_FILENO, prompt, idx);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
    g_signal = sig;
	redisplay_prompt();
}

void	init_signals(void)
{
	g_signal = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	update_exit_status(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
	if (data->exit_status == 128 + SIGINT)
		write(1, "\n", 1);
}

void	check_sigint(t_data *data)
{
	if (g_signal != 0)
	{
		data->exit_status = 128 + g_signal;
		g_signal = 0;
	}
}
