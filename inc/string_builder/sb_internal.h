/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:51:31 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 13:00:24 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SB_INTERNAL_H
# define SB_INTERNAL_H

# include "minishell.h"

int		ft_itostr(int n, char *buf);
size_t	count_digits(int n);

#endif /* SB_INTERNAL_H */