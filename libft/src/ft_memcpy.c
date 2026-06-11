/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:39:17 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 21:02:18 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (n == 0 || (!dest && !src))
		return (dest);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}
