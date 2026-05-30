/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:49:48 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/30 15:07:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stddef.h>

typedef struct s_prompt
{
	char	buffer[2048];
	size_t	len;
	size_t	max_len;
}	t_prompt;

void	generate_prompt(t_prompt *prompt);
void	init_prompt(t_prompt *prompt);

#endif /* PROMPT_H */