/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:29:38 by guillsan          #+#    #+#             */
/*   Updated: 2026/07/01 11:38:12 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*ptr;

	ptr = s;
	while (n--)
	{
		*(unsigned char *)ptr = c;
		ptr++;
	}
	return (s);
}
