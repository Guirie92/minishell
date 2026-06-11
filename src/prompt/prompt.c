/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:38:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 21:24:03 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "init.h"
#include "prompt/prompt.h"
#include "prompt/prompt_internal.h"
#include "string_builder/string_builder.h"
#include <stdio.h>
#include <unistd.h>

void	init_prompt(t_prompt *prompt)
{
	prompt->buffer[0] = '\0';
	prompt->len = 0;
	prompt->max_len = 2048;
}

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

static void	build_prompt(t_prompt *prompt, t_prompt *tmp)
{
	ft_strlcpy(prompt->buffer, CLR_BLUE "\n", prompt->max_len);
	ft_strlcat(prompt->buffer, tmp->buffer, prompt->max_len);
	prompt->len = ft_strlen(prompt->buffer);
}

void	generate_prompt(t_prompt *prompt)
{
	t_prompt	tmp;
	char		cwd[1024];
	int			git_root;

	init_prompt(&tmp);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		prompt->buffer[0] = '$';
		prompt->buffer[1] = '\0';
		return ;
	}
	git_root = find_git_root(prompt, cwd);
	if (git_root == E_SUCCESS)
		write_git_path(&tmp, cwd, prompt->buffer);
	else
		replace_home(&tmp, cwd);
	build_prompt(prompt, &tmp);
	//write(STDIN_FILENO, prompt->buffer, prompt->len);
	ft_strlcat(prompt->buffer, CLR_PURPLE TEXT_BOLD "\n> " 
		TEXT_UNBOLD CLR_RESET, prompt->max_len);
    prompt->len = ft_strlen(prompt->buffer);
}
