/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:29 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:07 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Redirect stdin to read from the heredoc file.
/// @param filename The name of the heredoc file.
/// @return 0 on success, -1 on failure.
int	redirect_stdin_to_heredoc(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_perror("open\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_perror("dup2\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/// @brief Build the filename for the heredoc file.
/// @param shell The minishell structure.
/// @param heredoc_index The index of the heredoc.
/// @return The constructed filename.
static char	*build_heredoc_filename(t_minishell *shell, int heredoc_index)
{
	char	*index_str;

	index_str = ft_itoa(heredoc_index);
	if (!index_str)
	{
		ft_perror("ft_itoa failed\n");
		return (NULL);
	}
	ft_strcpy(shell->heredoc_fname, ".heredoc_");
	ft_strcat(shell->heredoc_fname, index_str);
	ft_strcat(shell->heredoc_fname, ".txt");
	free(index_str);
	return (shell->heredoc_fname);
}

/// @brief Handle cleanup for heredoc.
/// @param fd The file descriptor of the heredoc file.
/// @param fname The name of the heredoc file.
/// @return -1 indicating failure.
static int	handle_heredoc_cleanup(int fd, char *fname)
{
	close(fd);
	unlink(fname);
	setup_sig_handle();
	return (-1);
}

/// @brief Handle signal flag for heredoc.
/// @return -1 indicating failure..
static int	handle_signal_flag(void)
{
	dup2(1, STDIN_FILENO);
	setup_sig_handle();
	return (-1);
}

/// @brief Handle the heredoc process.
/// @param token The token containing heredoc information.
/// @param heredoc_index The index of the heredoc.
/// @param shell The minishell structure.
/// @return 0 on success, -1 on failure.
int	handle_heredoc(t_token *token, int heredoc_index, t_minishell *shell)
{
	int		fd;
	char	*fname;

	fname = build_heredoc_filename(shell, heredoc_index);
	if (!fname)
		return (-1);
	fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	setup_sig_handle_heredoc();
	if (read_heredoc_lines(fd, token->next->data) == -1)
		return (handle_heredoc_cleanup(fd, fname));
	if (g_signal_flag == 1)
		return (handle_signal_flag());
	close(fd);
	setup_sig_handle();
	return (0);
}
