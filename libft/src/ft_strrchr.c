/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:29:18 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 21:03:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			ptr = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (ptr);
}
