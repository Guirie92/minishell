/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:56:23 by guillsan          #+#    #+#             */
/*   Updated: 2026/05/29 12:43:58 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>

# define CLR_GREEN  	"\001\033[32m\002"
# define CLR_BLUE   	"\001\033[34m\002"
# define CLR_YELLOW 	"\001\033[33m\002"
# define CLR_CYAN   	"\001\033[36m\002"
# define CLR_GREY       "\001\033[90m\002"
# define CLR_PURPLE     "\001\033[35m\002"
# define CLR_RESET      "\001\033[0m\002"

# define CLR_LIGHT_PURPLE  "\001\033[38;2;195;121;202m\002"
# define CLR_LIGHT_BLUE    "\001\033[38;2;98;152;230m\002"
# define CLR_LIGHT_GREY    "\001\033[38;2;156;156;156m\002"

# define TEXT_BOLD    "\033[1m"
# define TEXT_UNBOLD  "\033[22m"

typedef struct s_data
{
	char	*line;
}	t_data;

typedef struct s_prompt
{
	char	buffer[2048];
	size_t	len;
	size_t	max_len;
}	t_prompt;

typedef enum e_retcode
{
	E_SUCCESS = 0,
	E_FAILURE = 1
}	t_retcode;

/* prompt.c & prompt_utils.c */
void	generate_prompt(t_prompt *prompt);
void	init_prompt(t_prompt *prompt);
//void	scan_git_repo(char *cwd);
int		find_git_root(t_prompt *prompt, char *cwd);
void	write_git_path(t_prompt *prompt, const char *cwd, const char *git_root);
//char	*find_git_root(char *cwd);

/* utils */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif /* MINISHELL_H */