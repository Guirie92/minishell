/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:07:18 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 17:16:21 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digits(size_t n)
{
	size_t	dgts;

	dgts = 1;
	while (n >= 10)
	{
		n /= 10;
		dgts++;
	}
	return (dgts);
}
