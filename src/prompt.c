/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:38:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/29 04:53:46 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	write_cwd(t_prompt *prompt, const char *cwd, const size_t cwd_len)
{
	size_t	len;

	len = cwd_len;
	if (cwd_len >= prompt->max_len)
		len = prompt->max_len - 1;
	ft_strlcpy(&prompt->buffer[0], cwd, len + 1);
	prompt->len = ft_strlen(prompt->buffer);
}

static void	replace_home(t_prompt *prompt, const char *cwd)
{
	size_t			len;
	size_t			home_len;
	const size_t	cwd_len = ft_strlen(cwd);
	const char		*home = getenv("HOME");

	if (!home)
	{
		write_cwd(prompt, cwd, cwd_len);
		return ;
	}
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0)
	{
		len = cwd_len - home_len + 1;
		if (len >= prompt->max_len - 1)
			len = prompt->max_len - 2;
		prompt->buffer[0] = '~';
		ft_strlcpy(&prompt->buffer[1], cwd + home_len, len + 1);
		prompt->len = ft_strlen(prompt->buffer);
		return ;
	}
	write_cwd(prompt, cwd, cwd_len);
}

void	generate_prompt(t_prompt *prompt)
{
	char	cwd[1024];
	char	*folder;
	char	*branch;

	prompt->buffer[0] = '\0';
	if (!getcwd(cwd, sizeof(cwd)))
	{
		prompt->buffer[0] = '$';
		prompt->buffer[1] = '\0';
		return ;
	}
	(void)folder;
	(void)branch;

	printf("path: %s", cwd);
	replace_home(prompt, cwd);
}
