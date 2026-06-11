/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:29:57 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 21:03:22 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = 0;
	i = 0;
	while (dstlen < size && dst[dstlen])
		dstlen++;
	if (dstlen == size)
		return (size + srclen);
	dst += dstlen;
	while (src[i] && (dstlen + i + 1) < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstlen + i < size)
		dst[i] = '\0';
	return (dstlen + srclen);
}
