/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_alpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:38:02 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 19:56:14 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "libft.h"

static void	swap_env_nodes(t_env **a, t_env **b)
{
	t_env	*tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Sorts an array of environment variable nodes alphabetically by key.
 *
 * It iterates through the array comparing adjacent keys using ft_strcmp. 
 * 
 * If a key is found to be greater (the return value of ft_strcmp) than
 * the next (ft_strcmp > 0), the nodes are swapped.
 * 
 * 
 * ***** How ft_strcmp determines order (ASCII evaluation) *****
 * 
 * - If env_arr[j] is 'A' (65) and env_arr[j+1] is 'B' (66):
 *   65 - 66 = -1 (Negative) --> correct order, NO SWAP.
 * 
 * - If env_arr[j] is 'B' (66) and env_arr[j+1] is 'A' (65):
 *   66 - 65 = 1  (Positive) --> wrong order, SWAP.
 * 
 * 
 * In the inner loop (j), we go up till the reserve of the outer loop (i), which
 * it exactly is "(count - i - 1)".
 * This is, say count == 20:
 * - For the outer loop (i), we process iterations up to:  0,  1,  2,  ...  18
 * - For the inner loop (j), we process iterations up to: 18, 17, 16,  ...   1
 * 
 * 
 *  Example: 
 * 
 *  arr: [ B, D, A, C ] (count = 4) : (3 i iters)
 * 
 *  i == 0: (j < 4 - 0 - 1) --> (j < 3) : (3 iters)
 *                     CHAR      ASCII              ACTION       ARRAY-SNAPSHOT
 *   - j[0] vs j[1]  (B vs D):  66 - 68  =  -2  --> Sorted  -->  [ B, D, A, C ]
 *   - j[1] vs j[2]  (D vs A):  68 - 65  =   3  --> SWAP    -->  [ B, A, D, C ]
 *   - j[2] vs j[3]  (D vs C):  68 - 67  =   1  --> SWAP    -->  [ B, A, C, D ]
 * 
 * 
 *  i == 1: (j < 4 - 1 - 1) --> (j < 2) : (2 iters)
 *                     CHAR      ASCII              ACTION       ARRAY-SNAPSHOT
 *   - j[0] vs j[1]  (B vs A):  66 - 65  =   1  --> SWAP    -->  [ A, B, C, D ]
 *   - j[1] vs j[2]  (B vs C):  66 - 67  =  -1  --> Sorted  -->  [ A, B, C, D ]
 * 
 * 
 *  i == 2: (j < 4 - 2 - 1) --> (j < 1) : (1 iter)
 *                     CHAR      ASCII              ACTION       ARRAY-SNAPSHOT
 *   - j[0] vs j[1]  (A vs B):  65 - 66  =  -1  --> Sorted  -->  [ A, B, C, D ]
 * 
 */
static void	key_based_bubblesort(t_env **envp, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(envp[j]->key, envp[j + 1]->key) > 0)
				swap_env_nodes(&envp[j], &envp[j + 1]);
			j++;
		}
		i++;
	}
}

static void	print_ordered_envp(t_env **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_printf("declare -x %s", envp[i]->key);
		if (envp[i]->value)
			ft_printf("=\"%s\"", envp[i]->value);
		ft_printf("\n");
		i++;
	}
}

static void	populate_envp(t_data* data, t_env *node, t_env **envp)
{
	int	i;

	i = 0;
	node = data->env;
	while (node)
	{
		envp[i] = node;
		node = node->next;
		i++;
	}
}

void	print_env_alpha_order(t_data *data)
{
	t_env	**envp_tmp;
	t_env	*node;
	int		count;

	count = 0;
	node = data->env;
	while (node)
	{
		count++;
		node = node->next;
	}
	envp_tmp = malloc(count * sizeof(*envp_tmp));
	if (!envp_tmp)
		exit_with_error(data);
	populate_envp(data, node, envp_tmp);
	key_based_bubblesort(envp_tmp, count);
	print_ordered_envp(envp_tmp, count);
	free(envp_tmp);
}
