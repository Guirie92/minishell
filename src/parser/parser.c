/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:46:37 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/04 17:16:38 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

void	parser(t_data *data)
{
	t_pipeline	pipeline;
	
	pipeline.cmds = NULL;
	pipeline.cmdsc = 0;
	(void)pipeline;
	(void)data;
}
