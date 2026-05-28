/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:38:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/28 12:11:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	generate_prompt(t_prompt *prompt)
{
	char	cwd[1024];
	char	*folder;
	char	*branch;

	prompt->buffer[0] = '\0';
	if (!getcwd(cwd, sizeof(cwd)))
	{
		prompt->buffer[0] = '$';
		prompt->buffer[1] = ' ';
		prompt->buffer[2] = '\0';
		return ;
	}
	(void)folder;
	(void)branch;

	printf("path: %s", cwd);
}
