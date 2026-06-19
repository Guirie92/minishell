/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 23:30:40 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 23:32:09 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "clear_resources/clear_resources.h"
#include "error/error.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

void	exit_with_error(t_data *data)
{
	const int	saved_errno = errno;
	char		*sys_err;

	if (saved_errno != 0)
	{
		sys_err = strerror(saved_errno);
		ft_dprintf(STDERR_FILENO, ERROR_CLR "%s\n" CLR_RST, sys_err);
	}
	clear_data(data);
	exit(EXIT_FAILURE);
}