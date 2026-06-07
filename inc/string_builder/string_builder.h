/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 05:05:01 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 13:38:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUILDER_H
# define STRING_BUILDER_H

# include "minishell.h"
# include <limits.h>

# define INT_MIN_STR "2147483648"

typedef struct s_builder
{
	char	buf[2048];
	char	*ptr;
	size_t	size;
	size_t	remaining;
}	t_builder;

void	builder_init(t_builder *b);
void	builder_append(t_builder *b, const char *str);
void	builder_append_nbr(t_builder *b, int n);

#endif /* STRING_BUILDER_H */