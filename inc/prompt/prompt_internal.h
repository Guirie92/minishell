/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:49:45 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/31 14:41:59 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_INTERNAL_H
# define PROMPT_INTERNAL_H

# include "prompt/prompt.h"

int		find_git_root(t_prompt *prompt, char *cwd);
void	write_git_path(t_prompt *prompt, const char *cwd, const char *git_root);

#endif /* PROMPT_INTERNAL_H */