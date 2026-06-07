/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:32:09 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 13:19:24 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "clear_resources/clear_resources.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

void	print_warning(t_err_type err)
{
	const char	*err_msg = errmsg(err);

	ft_dprintf(STDERR_FILENO, WARNING_CLR ERR_MINISHELL_PREFFIX
		"%s\n" CLR_RST, err_msg);
}

void	print_warning_arg(t_err_type err, char *arg)
{
	const char	*err_msg = errmsg(err);

	ft_dprintf(STDERR_FILENO, WARNING_CLR ERR_MINISHELL_PREFFIX);
	ft_dprintf(STDERR_FILENO, err_msg, arg);
	ft_dprintf(STDERR_FILENO, "\n" CLR_RST);
}
