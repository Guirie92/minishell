/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:04:14 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/16 17:05:42 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MEM_FAIL	1
#define MEM_OK		0

static size_t	count_strings(char const *s, char c, size_t *len)
{
	size_t	i;
	size_t	count;

	if (!*s)
		return (0);
	i = 0;
	count = 1;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			count++;
		else if (s[i] != c && s[i] != '\0')
			(*len)++;
		i++;
	}
	return (count);
}

static int	count_substring_alloc(char **ptr_arr,
	char const *s, char c, size_t *i)
{
	size_t	count;
	size_t	start;

	count = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i])
	{
		if (s[*i] != c && s[*i] != '\0')
			count++;
		else
			break ;
		(*i)++;
	}
	*ptr_arr = malloc((count + 1) * sizeof(char));
	if (*ptr_arr == NULL)
		return (MEM_FAIL);
	ft_strlcpy(*ptr_arr, &s[start], count + 1);
	return (MEM_OK);
}

static void	free_mem(char **ptr_arr)
{
	size_t	i;

	i = 0;
	while (ptr_arr[i])
		free(ptr_arr[i++]);
	free(ptr_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr_arr;
	size_t	count;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	count = count_strings(s, c, &len);
	ptr_arr = ft_calloc(count + 1, sizeof(char *));
	if (!ptr_arr)
		return (NULL);
	len = 0;
	i = 0;
	while (i < count)
	{
		if (count_substring_alloc(&ptr_arr[i], s, c, &len) == MEM_FAIL)
		{
			free_mem(ptr_arr);
			return (NULL);
		}
		i++;
	}
	return (ptr_arr);
}
