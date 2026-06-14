/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:08:10 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/14 20:42:59 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "expander/expander.h"

/*
 * It calculates the expansion in a heredoc line, one at a time
 * (doesn't need quote context)
 */
size_t	calculate_expanded_len(t_data *data, char *line, int *b_has_expanded)
{
	size_t	len;

	len = 0;
	while (*line)
	{
		if (*line == '$')
		{
			*b_has_expanded = 1;
			calculate_env_len(data, &line, &len);
		}
		else
		{
			line++;
			len++;
		}
	}
	return (len);
}

/*
 * It performs 2 actions in 3 steps: it expands env variables and strips quotes
 * 
 * #1 - It calculates the new len, taking into account (1) quote removal
 *      and (2) expansion (env key into env value)
 * 
 * #2 - allocates the new length
 * 
 * #3 - and writes directly into the new buffer, without quotes, and with env
 *      values expanded
 */
void	expand_strip_redirs(t_data *data, t_redir *redir)
{
	char	*dst;
	size_t	len;
	int		b_has_quotes;

	while (redir)
	{
		if (redir->type == HEREDOC || !redir->target)
		{
			redir = redir->next;
			continue ;
		}
		len = calculate_token_len(data, redir->target, &b_has_quotes);
		dst = malloc((len + 1) * sizeof(char));
		if (!dst)
			exit_with_error(data);
		process_token_string(data, redir->target, dst);
		free(redir->target);
		redir->target = dst;
		redir = redir->next;
	}
}

/*
 * Array Shift (similar to move zeroes from leetcode):
 * https://leetcode.com/problems/move-zeroes/
 * solutions/6743967/video-two-pointer-solution-by-niits-m0fp/
 * 
 * This is a two pointer (or indices) shift pattern with O(n) time and O(1)
 * space complexities.
 * 
 * The idea is to have one index (read_idx)to iterate through the array, 
 * while the second index (write_idx) should only advance on non-null elements.
 * On non-null elements, the write_idx is assign the read_idx, which normally
 * will be more advance down the list, therefore shifting elements from right
 * to left.
 * 
 * For example: ["echo", NULL, "hello", NULL]:
 * 
 * - write[0] == echo, read[0] == echo
 *   write = read -> (EQUAL) -----> ["echo", NULL, "hello", NULL]
 *
 * - write[1] == NULL, read[1] == NULL
 *   read is null -> (DOES NOTHING) ["echo", NULL, "hello", NULL]
 * 
 * - write[1] == NULL, read[2] == "hello"
 *   write = read ----------------> ["echo", "hello", "hello", NULL]
 * 
 * - write[2] == "hello", read[3] == "NULL"
 *   read is null -> (DOES NOTHING) ["echo", "hello", "hello", NULL]
 * 
 *   The LOOP ends, and we're at write_idx == 2. So we make it null:
 *   ["echo", "hello", NULL, NULL]
 * 
 *   ARRAY SORTED (you could also do swaps and it works the same)
 */
static void	arrange_argv_array(t_cmd *cmd)
{
	int	rd_i;
	int	wr_i;

	rd_i = 0;
	wr_i = 0;
	if (cmd->argc < 1)
		return ;
	while (rd_i < cmd->argc)
	{
		if (cmd->argv[rd_i] != NULL)
		{
			cmd->argv[wr_i] = cmd->argv[rd_i];
			wr_i++;
		}
		rd_i++;
	}
	cmd->argv[wr_i] = NULL;
	cmd->argc = wr_i;
}

/*
 * It performs 3 actions: it expands env variables, strips quotes, and removes
 * empty tokens IF there's no quotes and the expansion results in an empty str
 * 
 * #1 - It calculates the new len, taking into account (1) quote removal
 *      and (2) expansion (env key into env value)
 * 
 * #2 - allocates the new length
 * 
 * #3 - and writes directly into the new buffer, without quotes, and with env
 *      values expanded
 */
static void	expand_strip_argv(t_data *data, t_cmd *cmd)
{
	char	*dst;
	size_t	len;
	int		i;
	int		b_has_quotes;

	i = 0;
	while (i < cmd->argc)
	{
		len = calculate_token_len(data, cmd->argv[i], &b_has_quotes);
		if (len == 0 && !b_has_quotes)
		{
			free(cmd->argv[i]);
			cmd->argv[i++] = NULL;
			continue ;
		}
		dst = malloc((len + 1) * sizeof(char));
		if (!dst)
			exit_with_error(data);
		process_token_string(data, cmd->argv[i], dst);
		free(cmd->argv[i]);
		cmd->argv[i] = dst;
		i++;
	}
}

void	resolve_pipeline(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->pipeline->cmds;
	while (cmd)
	{
		expand_strip_argv(data, cmd);
		arrange_argv_array(cmd);
		expand_strip_redirs(data, cmd->redirs);
		cmd = cmd->next;
	}
}
