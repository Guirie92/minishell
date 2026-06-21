/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:19:19 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/22 00:12:44 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "init.h"
#include "prompt/prompt.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_prompt	prompt;

	(void)argc;
	(void)argv;
	data.prompt = &prompt;
	init_data(&data, envp);
	init_signals();
	shell_loop(&data);
	return (0);
}
