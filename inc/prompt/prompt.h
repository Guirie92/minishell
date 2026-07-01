/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:49:48 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 14:00:08 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# include <stddef.h>

# define PROMPT_SIZE BUFFER_SIZE

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

typedef struct s_prompt
{
	char	buffer[PROMPT_SIZE];
	char	*prefix;
	char	*suffix;
	size_t	len;
	size_t	max_len;
	size_t	usable_len;
}	t_prompt;

void	init_prompt(t_prompt *prompt);
void	generate_prompt(t_data *data, t_prompt *prompt);

#endif /* PROMPT_H */