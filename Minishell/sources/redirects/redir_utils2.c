/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:00 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:01 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Add a space after a redirection character in a string.
/// @param arg The original string containing the redirection character.
/// @return A new string with a space added after the redir character, or NULL.
char	*add_space_after_redirection(const char *arg)
{
	char	*new_arg;
	size_t	len;

	len = ft_strlen(arg);
	new_arg = malloc(len + 2);
	if (!new_arg)
		return (NULL);
	new_arg[0] = arg[0];
	new_arg[1] = ' ';
	ft_strcpy(new_arg + 2, arg + 1);
	return (new_arg);
}

/// @brief Save the original file descriptors for stdin and stdout.
/// @param original_stdin Pointer to store the original stdin file descriptor.
/// @param original_stdout Pointer to store the original stdout file descriptr.
/// @return 0 on success, -1 on failure.
int	save_original_fds(int *original_stdin, int *original_stdout)
{
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
	{
		ft_perror("dup\n");
		return (-1);
	}
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdout == -1)
	{
		ft_perror("dup\n");
		close(*original_stdin);
		return (-1);
	}
	return (0);
}

/// @brief Restore the original file descriptors for stdin and stdout.
/// @param original_stdin The original stdin file descriptor.
/// @param original_stdout The original stdout file descriptor.
void	restore_original_fds(int original_stdin, int original_stdout)
{
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		ft_perror("dup2\n");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		ft_perror("dup2\n");
	close(original_stdin);
	close(original_stdout);
}

int	check_stat_and_errors(char *dir)
{
	struct stat	st;

	if (stat(dir, &st) == -1)
	{
		if (errno == EACCES)
			permission_denied_error(dir);
		else
			n_f_o_d_error(dir);
		return (-1);
	}
	if (!S_ISDIR(st.st_mode))
	{
		n_f_o_d_error(dir);
		return (-1);
	}
	return (0);
}

int	check_directory(char *path)
{
	char		*dir;
	char		*last_slash;

	dir = ft_strdup(path);
	if (!dir)
		return (-1);
	last_slash = ft_strrchr(dir, '/');
	if (last_slash)
		*last_slash = '\0';
	if (last_slash && check_stat_and_errors(dir) == -1)
	{
		free(dir);
		return (-1);
	}
	free(dir);
	return (0);
}
