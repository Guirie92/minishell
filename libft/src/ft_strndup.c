/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:51:26 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/11 21:03:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;
	size_t	len;

	len = 0;
	while (s[len] && len < n)
		len++;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr)
		ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}
