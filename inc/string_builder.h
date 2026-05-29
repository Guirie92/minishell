/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 05:05:01 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/29 05:10:00 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUILDER_H
# define STRING_BUILDER_H

# include "minishell.h"

typedef struct s_builder
{
	char	*buf;
	char	*ptr;
	size_t	remaining;
}	t_builder;

void	builder_init(t_builder *b, char *buffer, size_t size);
void	builder_append(t_builder *b, const char *str);

#endif /* STRING_BUILDER_H */