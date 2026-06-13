/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/12 22:40:46 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "expander/expander.h"
#include "libft.h"
#include "parser/parser.h"

size_t	get_key_len(char *line, char **str, size_t *i)
{
	size_t	var_len;

	var_len = 0;
	if (ft_isdigit(line[*i]))
	{
		(*i)++;
		return (0);
	}
	*str = &line[*i];
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		var_len++;
		(*i)++;
	}
	return (var_len);
}

static void	handle_dollar_sign(t_data *data, char *line, size_t *len, size_t *i)
{
	size_t	var_len;
	char	*str;
	t_env	*env_node;

	var_len = 0;
	env_node = NULL;
	str = NULL;
	(*i)++;
	if (validate_env_key(line[*i]))
	{
		if (line[*i] == '?')
		{
			*len += ft_count_digits(data->exit_status);
			(*i)++;
		}
		else
			var_len = get_key_len(line, &str, i);
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
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			*b_has_expanded = 1;
			handle_dollar_sign(data, line, &len, &i);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
