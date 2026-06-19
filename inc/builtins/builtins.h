/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:42:40 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/19 18:09:11 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>

# define BUILTIN_COUNT 7

# define BUILTIN_N1 "echo"
# define BUILTIN_N2 "cd"
# define BUILTIN_N3 "pwd"
# define BUILTIN_N4 "export"
# define BUILTIN_N5 "unset"
# define BUILTIN_N6 "env"
# define BUILTIN_N7 "exit"

# define BUILTIN_F1 &process_echo
# define BUILTIN_F2 &process_cd
# define BUILTIN_F3 &process_pwd
# define BUILTIN_F4 &process_export
# define BUILTIN_F5 &process_unset
# define BUILTIN_F6 &process_env
# define BUILTIN_F7 &process_exit

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;
typedef void	(*t_builtin_func)(t_data *, t_cmd *);

typedef struct s_builtins
{
	t_builtin_func	funcs[BUILTIN_COUNT];
	char			*names[BUILTIN_COUNT];
	size_t			len[BUILTIN_COUNT];
}	t_builtins;

/* init */
void	builtins_init(t_data *data);

/* built-ins */
void	process_echo(t_data *data, t_cmd *cmd);
void	process_cd(t_data *data, t_cmd *cmd);
void	process_pwd(t_data *data, t_cmd *cmd);
void	process_export(t_data *data, t_cmd *cmd);
void	process_unset(t_data *data, t_cmd *cmd);
void	process_env(t_data *data, t_cmd *cmd);
void	process_exit(t_data *data, t_cmd *cmd);

#endif /* BUILTINS_H */