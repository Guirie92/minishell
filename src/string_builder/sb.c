/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 05:08:51 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 13:44:27 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_builder/string_builder.h"
#include "string_builder/sb_internal.h"

void	builder_init(t_builder *b)
{
	b->ptr = b->buf;
	b->size = 2048;
	b->remaining = b->size;
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

void	builder_append_nbr(t_builder *b, int n)
{
	size_t	len;

	if (b->remaining <= 1)
		return ;
	len = (size_t)count_digits(n);
	if (n < 0 || n == INT_MIN)
		len++;
	if (len >= b->remaining)
		return ;
	ft_itostr(n, b->ptr);
	b->ptr += len;
	*(b->ptr) = '\0';
	b->remaining -= len;
}
