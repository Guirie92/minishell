/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:56:23 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/28 12:02:20 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

# define CLR_GREEN  	"\001\033[32m\002"
# define CLR_BLUE   	"\001\033[34m\002"
# define CLR_YELLOW 	"\001\033[33m\002"
# define CLR_CYAN   	"\001\033[36m\002"
# define CLR_RESET  	"\033[37m"

# define CLR_LIGHT_PURPLE  "\001\033[38;2;195;121;202m"
# define CLR_LIGHT_BLUE    "\001\033[38;2;98;152;230m"
# define CLR_LIGHT_GREY    "\001\033[38;2;156;156;156m"

typedef struct s_data
{
	char	*line;
}	t_data;

typedef struct s_prompt
{
	char	buffer[2048];
	int		len;
	int		max_len;
}	t_prompt;

/* prompt.c */
void	generate_prompt(t_prompt *prompt);

#endif /* MINISHELL_H */