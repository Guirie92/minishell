/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:55:56 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/28 22:43:13 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser/parser.h"

/**
 * The idea of this check is to prevent computing res first (which could
 * overflow) and then compare it against LLONG_MAX and/or LLONG_MIN
 * 
 * So, to avoid 2 separate functions (as I had before), if we simply do
 * LLONG_MIN, which also comprises LLONG_MAX, we can build our res as a
 * negative number so that we can go to that very last digit because of the
 * extra +1 (that extra bit) the negative has since it doesn't have to count
 * the 0 as the positive realm does. Of course, this requires invalidating
 * the result if we happen to be working with a possitive number (determined
 * by the passed in "sign") and the result is == LLONG_MIN (it will never
 * be greater 'cause we invalidate them).
 * 
 * The idea is quite simple, with a double check:
 * 
 * (1) res can never be greater than LLONG_MIN / 10, or else it will immediately
 *     overflow as we multiply by 10.
 * 
 * (2) If it's not greater, then we check if it's equal, because if it's less,
 *     no matter how much you multiply it by ten and you add any digit (0-9) to
 *     it, it will never overflow. So, in this case, if it's equal, then we
 *     check if the digit we have at hand is greater than the very last digit
 *     of LLONG_MIN. For example, say we have this simplified case:
 *     
 *          - LLONG_MIN  = -1321
 *          - our number = -1320
 *          
 *          then, as we are approaching the last iter (-132), we check if it's
 *          greater than -1321 / 10 (-132), and since it's not, then we move
 *          on to the next check: -132 == -1321 / 10 (-132) --> Yep,
 *          so the last digit matters. Our current digit here is 0, and the
 *          last digit og our fake LLONG_MIN is 1, so: 0 > 1? --> Nope,
 *          so we can safely multiply our current res (-132) by 10 and we can
 *          also safely add the current digit to it (-1321) without causing a
 *          nasty overflow.
 */
static int	process_digits(char *str, int i, int sign)
{
	long long	res;
	int			digit;

	res = 0;
	digit = 0;
	while (str[i])
	{
		digit = str[i] - '0';
		if (!ft_isdigit(str[i]))
			return (E_FAILURE);
		if (res < LLONG_MIN / 10)
			return (E_FAILURE);
		if (res == LLONG_MIN / 10 && digit > ft_abs(LLONG_MIN % 10))
			return (E_FAILURE);
		res = (res * 10) - digit;
		i++;
	}
	if (sign > 0 && res == LLONG_MIN)
		return (E_FAILURE);
	return (E_SUCCESS);
}

static int	validate_nbr(char *str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
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
	return (process_digits(str, i, sign));
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
