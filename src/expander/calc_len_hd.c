/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/13 21:29:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "expander/expander.h"
#include "libft.h"
#include "parser/parser.h"

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

void	calc_env_from_d_sign(t_data *data, char **line, size_t *len)
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

size_t	calculate_expanded_len(t_data *data, char *line, int *b_has_expanded)
{
	size_t	len;

	len = 0;
	while (*line)
	{
		if (*line == '$')
		{
			*b_has_expanded = 1;
			calc_env_from_d_sign(data, &line, &len);
		}
		else
		{
			line++;
			len++;
		}
	}
	return (len);
}
