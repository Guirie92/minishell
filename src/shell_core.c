/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:07:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/08 15:36:14 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "executor/executor.h"

void	process_input(t_data *data)
{
	if (lexer(data) != E_SUCCESS)
		return ;
	if (parser(data) != E_SUCCESS)
		return ;
	if (heredoc_collector(data) != E_SUCCESS)
		return ;

	//TODO:
	// expander(parsed_cmds)
	// executor(parsed_cmds)
}
