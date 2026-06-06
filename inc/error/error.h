/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:35:58 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/07 00:33:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define WARNING_CLR      "\033[33m"
# define ERROR_CLR        "\033[31m"

# define ERR_MINISHELL_PREFFIX "minishell: "
# define WARNING_PREFFIX       "warning: "

typedef enum e_err_type
{
	ERR_UNCLOSED_QUOTES,
	ERR_INVALID_REDIR,
	ERR_UNEXPECTED_TOKEN,
	ERR_HEREDOC_EOF,
	ERR_CMD_NOT_FOUND,
	ERR_COUNT
}	t_err_type;

typedef struct s_data	t_data;

const char	*errmsg(t_err_type id);
void		exit_with_error(t_data *data);
void		print_warning(t_err_type err_code);
void		print_warning_arg(t_err_type err_code, char *arg);
void		print_error(t_err_type err_code);
void		print_error_arg(t_err_type err_code, char *arg);

#endif /* ERROR_H */