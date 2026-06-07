/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:47:59 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 13:09:46 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_builder/string_builder.h"

static void	itochr(char *s, int n)
{
	if (n > 9)
		itochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

size_t	count_digits(int n)
{
	size_t	dgts;

	dgts = 0;
	if (n == 0)
		dgts++;
	while (n > 0)
	{
		n /= 10;
		dgts++;
	}
	return (dgts);
}

static void	process_negative(int *n, char **buf, size_t *dgts)
{
	if (*n < 0)
	{
		(*buf)[(*dgts)++] = '-';
		(*n) = -(*n);
	}
}

int	ft_itostr(int n, char *buf)
{
	size_t		dgts;
	const char	*int_min = INT_MIN_STR;

	if (!buf)
		return (0);
	dgts = 0;
	if (n == INT_MIN)
	{
		buf[dgts++] = '-';
		while (*int_min)
			buf[dgts++] = *int_min++;
		buf[dgts] = '\0';
		return (dgts);
	}
	process_negative(&n, &buf, &dgts);
	dgts += count_digits(n);
	itochr(&buf[dgts - 1], n);
	buf[dgts] = '\0';
	return (dgts);
}
