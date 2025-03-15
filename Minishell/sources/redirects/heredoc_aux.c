/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:11 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:12 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Appends a line of text to the current heredoc content.
/// Concatenates the current heredoc content with the new line of text.
/// @param content The current heredoc content.
/// @param line The new line to append.
/// @return A pointer to the updated heredoc content.
static char	*append_line(char *content, char *line)
{
	char	*temp;

	temp = ft_strjoin(content, line);
	free(content);
	content = temp;
	temp = ft_strjoin(content, "\n");
	free(content);
	return (temp);
}

/// @brief Processes a single line of heredoc input.
/// @param delimiter The heredoc delimiter string.
/// @param pcontent A pointer to the pointer to the current heredoc content.
/// @return -2 signal interruption, 1 line is the delimiter,  0 on success.
static int	process_heredoc_line(const char *delimiter, char **pcontent)
{
	char	*line;

	line = readline("");
	if (g_signal_flag)
	{
		free(line);
		return (-2);
	}
	if (line == NULL)
	{
		ft_perror(HEREDOC_WARNING);
		ft_perror(delimiter);
		ft_perror("')\n");
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	*pcontent = append_line(*pcontent, line);
	free(line);
	return (0);
}

/// @brief Collects heredoc input until the delimiter or termination.
/// @param delimiter The heredoc delimiter string.
/// @return PTR to heredoc content, (char *)-2 signal interruption, or NULL.
static char	*collect_heredoc(const char *delimiter)
{
	char	*content;
	int		ret;

	content = ft_strdup("");
	if (content == NULL)
		return (NULL);
	g_signal_flag = 0;
	while (1)
	{
		write(1, "> ", 2);
		ret = process_heredoc_line(delimiter, &content);
		if (ret != 0)
			break ;
	}
	if (g_signal_flag)
	{
		free(content);
		return ((char *)-2);
	}
	return (content);
}

/// @brief Reads heredoc input and writes it to a file descriptor.
/// @param fd The file descriptor to which the heredoc content will be written.
/// @param delimiter The heredoc delimiter string.
/// @return 0 on success, -1 on memory alloc error, or -2 for sig interruption.
int	read_heredoc_lines(int fd, const char *delimiter)
{
	char	*heredoc;

	heredoc = collect_heredoc(delimiter);
	if (heredoc == (char *)-2)
		return (-2);
	if (heredoc == NULL)
		return (-1);
	write(fd, heredoc, ft_strlen(heredoc));
	free(heredoc);
	return (0);
}
