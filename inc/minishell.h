/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:56:23 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/28 10:18:39 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CLR_GREEN  "\001\033[32m\002"
#define CLR_BLUE   "\001\033[34m\002"
#define CLR_YELLOW "\001\033[33m\002"
#define CLR_CYAN   "\001\033[36m\002"
#define CLR_RESET  "\001\033[0m\002"

typedef struct s_data
{
	char	*line;
}	t_data;
