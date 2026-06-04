/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:07:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/04 17:15:37 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

void	process_input(t_data *data)
{
	lexer(data);
	if (data->err_type == ERR_UNCLOSED_QUOTES)
	{
		custom_error_msg(ERR_UNCLOSED_QUOTES);
		return ;
	}
	parser(data);

	
	//TODO:
	// expander(parsed_cmds)
	// executor(parsed_cmds)
}
