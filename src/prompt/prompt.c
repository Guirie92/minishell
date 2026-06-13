/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:38:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 17:12:03 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "prompt/prompt.h"
#include "prompt/prompt_internal.h"
#include "string_builder/string_builder.h"
#include <unistd.h>

void	init_prompt(t_prompt *prompt)
{
	prompt->buffer[0] = '\0';
	prompt->len = 0;
	prompt->max_len = PROMPT_SIZE;
	prompt->prefix = CLR_BLUE "\n";
	prompt->suffix = CLR_PURPLE TEXT_BOLD "\n> " TEXT_UNBOLD CLR_RESET;
	prompt->reserved_len = ft_strlen(prompt->prefix)
		+ ft_strlen(prompt->suffix);
	prompt->usable_len = prompt->max_len - prompt->reserved_len - 1;
}

static void	write_cwd(t_prompt *prompt, const char *cwd)
{
	ft_strlcpy(prompt->buffer, cwd, prompt->usable_len + 1);
	prompt->len = ft_strlen(prompt->buffer);
}

static void	replace_home(t_prompt *prompt, const char *cwd)
{
	size_t			home_len;
	const char		*home = getenv("HOME");

	if (!home)
	{
		write_cwd(prompt, cwd);
		return ;
	}
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0)
	{
		prompt->buffer[0] = '~';
		ft_strlcpy(&prompt->buffer[1], cwd + home_len, prompt->usable_len);
		prompt->len = ft_strlen(prompt->buffer);
		return ;
	}
	write_cwd(prompt, cwd);
}

static void	build_prompt(t_prompt *prompt, t_prompt *tmp)
{
	ft_strlcpy(prompt->buffer, prompt->prefix, prompt->max_len);
	ft_strlcat(prompt->buffer, tmp->buffer, prompt->max_len);
	prompt->len = ft_strlen(prompt->buffer);
}

void	generate_prompt(t_prompt *prompt)
{
	t_prompt	tmp;
	char		cwd[PATH_MAX];
	char		git_root[PATH_MAX];

	init_prompt(prompt);
	init_prompt(&tmp);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_strlcpy(prompt->buffer, "minishell> ", prompt->max_len);
		return ;
	}
	if (find_git_root(git_root, cwd) == E_SUCCESS)
		write_git_path(&tmp, cwd, git_root);
	else
		replace_home(&tmp, cwd);
	build_prompt(prompt, &tmp);
	ft_strlcat(prompt->buffer, prompt->suffix, prompt->max_len);
	prompt->len = ft_strlen(prompt->buffer);
}
