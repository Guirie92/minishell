/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 19:15:59 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 20:49:25 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itochr(char *s, int n)
{
	if (n > 9)
		itochr(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static int	count_digits(int n, int *sign, size_t *count)
{
	int	num;

	num = n;
	if (n < 0)
	{
		(*count)++;
		*sign = -1;
		n = -n;
	}
	num = n;
	while (n > 9)
	{
		n /= 10;
		(*count)++;
	}
	return (num);
}

static void	print_int_min(char *tmp)
{
	const char	*int_min = "-2147483648";
	while (*int_min)
		*tmp++ = *int_min++;
	*tmp = '\0';
}

size_t	ft_itoa_buffer(int n, char *buf, size_t cap)
{
	size_t	count;
	int		sign;
	size_t	len;
	char	tmp[12];

	if (cap == 0)
		return (0);
	sign = 1;
	count = 1;
	if (n == INT_MIN)
		print_int_min(tmp);
	else
	{
		n = count_digits(n, &sign, &count);
		if (sign < 0)
			*tmp = '-';
		itochr(&tmp[count - 1], n);
		tmp[count] = '\0';
	}
	len = ft_strlen(tmp);
	if (len >= cap)
		len = cap - 1;
	ft_memcpy(buf, tmp, len);
	buf[len] = '\0';
	return (len);
}
