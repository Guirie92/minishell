/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 05:08:51 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/29 05:25:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_builder.h"

void	builder_init(t_builder *b, char *buffer, size_t size)
{
	b->buf = buffer;
	b->ptr = buffer;
	b->remaining = size;
	*(b->ptr) = '\0';
}

void	builder_append(t_builder *b, const char *str)
{
	size_t	len;

	if (b->remaining <= 1)
		return ;
	len = ft_strlen(str);
	if (len >= b->remaining)
		len = b->remaining - 1;
	ft_memcpy(b->ptr, str, len);
	b->ptr += len;
	*(b->ptr) = '\0';
	b->remaining -= len;
}
