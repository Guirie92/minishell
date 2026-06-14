/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_env_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 13:06:15 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 13:17:35 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env/env.h"
#include "expander/expander.h"

size_t	get_key_len(char **line, char **str)
{
	size_t	var_len;

	var_len = 0;
	if (ft_isdigit(**line))
	{
		(*line)++;
		return (0);
	}
	*str = *line;
	while (ft_isalnum(**line) || **line == '_')
	{
		var_len++;
		(*line)++;
	}
	return (var_len);
}

void	calculate_env_len(t_data *data, char **line, size_t *len)
{
	size_t	var_len;
	char	*str;
	t_env	*env_node;

	var_len = 0;
	env_node = NULL;
	str = NULL;
	(*line)++;
	if (validate_env_key(**line))
	{
		if (**line == '?')
		{
			*len += ft_count_digits(data->exit_status);
			(*line)++;
			return ;
		}
		else
			var_len = get_key_len(line, &str);
	}
	else
		(*len)++;
	if (var_len > 0)
		env_node = find_env(data, str, var_len);
	if (env_node)
		*len += ft_strlen(env_node->value);
}
