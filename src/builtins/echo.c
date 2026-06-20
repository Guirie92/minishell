/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:36:24 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/20 11:12:14 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

/*
 * Apparently, bash handles the following type of input for -n:
 *
 *   echo -n hello           --> (a single -n argument)
 *   echo -nnnn hello        --> (any number of trailing 'n's)
 *   echo -n -n -n hello     --> (multiple -n arguments)
 *   echo -n -nnn -n hello   --> (any combination of the previous)
 * 
 * So, I replaced my original approach:
 * `if (ft_strlen(cmd->argv[1]) == 2 && ft_strcmp(cmd->argv[1], "-n") == 0)`
 * 
 * with the `is_n` func.
 */
static int	is_n(char *s)
{
	int	i;

	if (!*s)
		return (0);
	if (s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	process_echo(t_data *data, t_cmd *cmd)
{
	size_t	i;
	int		b_n_opt;

	(void)data;
	i = 1;
	b_n_opt = 0;
	while (cmd->argv[i])
	{
		if (is_n(cmd->argv[i]))
			b_n_opt = 1;
		else
			break ;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!b_n_opt || i == 1)
		ft_printf("\n");
}
