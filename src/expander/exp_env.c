/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 13:07:11 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 13:24:46 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "expander/expander.h"

size_t	validate_env_key(unsigned char c)
{
	if (ft_isalnum(c) || c == '?' || c == '_')
		return (1);
	return (0);
}

static void	parse_env_key(t_data *data, char **src, char **dst)
{
	char	*start;
	t_env	*env_node;
	size_t	val_len;

	if (ft_isdigit(**src))
	{
		(*src)++;
		return ;
	}
	start = *src;
	while (ft_isalnum(**src) || **src == '_')
		(*src)++;
	if (start == *src)
		return ;
	env_node = find_env(data, start, *src - start);
	if (env_node)
	{
		val_len = ft_strlen(env_node->value);
		ft_strlcpy(*dst, env_node->value, val_len + 1);
		*dst += val_len;
	}
}

void	fill_env_key(t_data *data, char **src, char **dst)
{
	(*src)++;
	if (!validate_env_key(**src))
	{
		*(*dst)++ = '$';
		return ;
	}
	if (**src == '?')
	{
		*dst += ft_itoa_buffer(data->exit_status, *dst, INT_MAX_LEN);
		(*src)++;
		return ;
	}
	parse_env_key(data, src, dst);
}
