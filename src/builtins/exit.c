/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:55:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 18:45:03 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

/**
 * This checks for overflow without actually triggering it. 
 * Instead of (res * 10 + digit > MAX), which would wrap around,
 * we check if (res > (MAX - digit) / 10). 
 * Basically, it's asking "am I already too big to add another 
 * digit safely?" before doing the math.
 */
static int	process_digits(char *str, int i, unsigned long long res,
	unsigned long long limit)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (E_FAILURE);
		if (res > (limit - (str[i] - '0')) / 10)
			return (E_FAILURE);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (E_SUCCESS);
}

static int	validate_nbr(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	res = 0;
	if (!str[0])
		return (E_FAILURE);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (E_FAILURE);
	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = LLONG_MIN;
	return (process_digits(str, i, res, limit));
}

/**
 * Quick note on Exit on "non-numeric" error:
 * 
 * In Bash version:
 * GNU bash, version 5.1.16(1)-release (x86_64-pc-linux-gnu)
 * 
 * (and probably earlier versions) it appears to exit with exit-code "2",
 * that's why it's hardcoded there on `ERR_EXIT_NUMERIC`. It doesn't make
 * much sense, but we're trying to reproduce standard bash behavior.
 * 
 * However, in newer versions, like:
 * GNU bash, version 5.3.9(1)-release (aarch64-unknown-linux-gnu)
 * 
 * I've been testing it and it no longer seems to exit with exit-code 2:
 * It sets the exit_code to 2 (you can see it on echo $?), but it doesn't
 * terminate the current session (doesn't really exit),
 * so something to bear in mind (it looks more sensical to me)
 */
static	int	process_invalidations(t_data *data, t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		clear_data(data);
		exit(data->exit_status);
	}
	if (validate_nbr(cmd->argv[1]) != E_SUCCESS)
	{
		print_error_arg2(ERR_EXIT_NUMERIC, "exit", cmd->argv[1]);
		clear_data(data);
		exit(2);
	}
	if (cmd->argc > 2)
	{
		print_error_arg(ERR_EXIT_ARGS, "exit");
		data->exit_status = 1;
		if (!data->pipeline->cmds->next)
			return (E_FAILURE);
		else
		{
			clear_data(data);
			exit(EXIT_FAILURE);
		}
	}
	return (E_SUCCESS);
}

/**
 * Only prints when it's a single-command pipeline. This is, if `cmd->next`
 * is null, that means it is being called from the parent and we can print exit.
 */
void	process_exit(t_data *data, t_cmd *cmd)
{
	int	exit_code;

	if (!data->pipeline->cmds->next)
		ft_dprintf(STDOUT_FILENO, "exit\n");
	if (process_invalidations(data, cmd) != E_SUCCESS)
		return ;
	exit_code = ft_atoi(cmd->argv[1]);
	clear_data(data);
	exit(exit_code);
}
