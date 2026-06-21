/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 09:23:14 by guillsan          #+#    #+#             */
/*   Updated: 2026/06/21 18:45:55 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "prompt/prompt.h"
#include "fcntl.h"
#include "unistd.h"

static void	append_branch(t_prompt *prompt, char *buffer, int i)
{
	int	j;

	if (buffer[i] == '/')
		i++;
	else
		i = 0;
	j = prompt->len;
	while (buffer[i] && buffer[i] != '\n' && j < (int)prompt->usable_len)
		prompt->buffer[j++] = buffer[i++];
	prompt->buffer[j] = '\0';
	prompt->len = j;
}

/**
 * opens the file at .git/HEAD, which reports the refernce and it's
 * saved to buffer.
 * 
 * If you print the reference, it's something like:
 * "ref: refs/heads/master" (or main)
 * 
 * So, the idea is to extract the main, master, or the custom name for the
 * branch of the git repo
 * 
 * We scan for "/" from the end, and save it into our `prompt->buffer`
 */
static void	print_git_branch(t_prompt *prompt, char *git_root)
{
	char	path[PATH_MAX];
	char	buffer[256];
	int		fd;
	int		i;

	ft_strlcpy(path, git_root, sizeof(path));
	ft_strlcat(path, "/.git/HEAD", sizeof(path));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	i = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (i <= 0)
		return ;
	buffer[i] = '\0';
	if (buffer[i - 1] == '\n')
		buffer[i - 1] = '\0';
	i = ft_strlen(buffer) - 1;
	while (i > 0 && buffer[i] != '/')
		i--;
	append_branch(prompt, buffer, i);
}

/**
 * It skips git_root from cwd
 *
 * For example ->
 * 
 * `repo` basename:
 * /a/b/minishell -> minishell
 * 
 * `cwd`:
 * /a/b/minishell/src/parser
 *
 * `relative`:
 * /src/parser
 */
void	write_git_path(t_prompt *prompt, const char *cwd, const char *git_root)
{
	char	*repo;
	char	*relative;

	repo = ft_strrchr(git_root, '/');
	if (repo && *(repo + 1))
		repo++;
	else
		repo = (char *)git_root;
	relative = (char *)(cwd + ft_strlen(git_root));
	ft_strlcpy(prompt->buffer, TEXT_BOLD, prompt->usable_len + 1);
	ft_strlcat(prompt->buffer, repo, prompt->usable_len + 1);
	ft_strlcat(prompt->buffer, TEXT_UNBOLD, prompt->usable_len + 1);
	ft_strlcat(prompt->buffer, relative, prompt->usable_len + 1);
	ft_strlcat(prompt->buffer, CLR_GREY, prompt->usable_len + 1);
	ft_strlcat(prompt->buffer, " git:", prompt->usable_len + 1);
	prompt->len = ft_strlen(prompt->buffer);
	print_git_branch(prompt, (char *)git_root);
}

static int	has_git_dir(char *path)
{
	char	test[PATH_MAX];

	ft_strlcpy(test, path, sizeof(test));
	ft_strlcat(test, "/.git", sizeof(test));
	return (access(test, F_OK) == 0);
}

/**
 * This finds the full path until it reaches the current git repo.
 * 
 * The git root is saved in the prompt->buffer, but it's passed around as
 * `git_root`
 * 
 * (1) it checks first if the current folder has the git directory, and if so, 
 *     returns
 * (2) checks if it reached the root by checking if the first char in our buffer
 *     is "/", and if so, returns
 * (3) if not found, removes the current folder (goes back to the previous "/")
 * (4) we make sure to keep the "/" intact
 */
int	find_git_root(char *git_root, const char *cwd)
{
	int	i;

	ft_strlcpy(git_root, cwd, PATH_MAX);
	while (1)
	{
		if (has_git_dir(git_root))
			return (E_SUCCESS);
		if (ft_strcmp(git_root, "/") == 0)
			break ;
		i = ft_strlen(git_root) - 1;
		while (i > 0 && git_root[i] != '/')
			i--;
		if (i == 0)
			git_root[1] = '\0';
		else
			git_root[i] = '\0';
	}
	return (E_FAILURE);
}
