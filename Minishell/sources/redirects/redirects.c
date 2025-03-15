/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:45 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:46 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Set up redirections based on the token list.
/// @param token The head of the token list.
/// @param env_list The environment list.
/// @return 0 on success, -1 on failure.
// int	setup_redirections(t_token *token, t_minishell *shell)
// {
// 	char	*index_str;

// 	while (token && token->type != TOKEN_PIPE)
// 	{
// 		if (token->type == TOKEN_IN_REDIRECT)
// 		{
// 			if (setup_in_redirect(token, shell) == -1)
// 				return (-1);
// 		}
// 		else if (token->type == TOKEN_OUT_REDIRECT)
// 		{
// 			if (setup_out_redirect(token, shell) == -1)
// 				return (-1);
// 		}
// 		else if (token->type == TOKEN_APPEND_REDIRECT)
// 		{
// 			if (setup_append_redirect(token, shell) == -1)
// 				return (-1);
// 		}
// 		else if (token->type == TOKEN_HEREDOC)
// 		{
// 			index_str = ft_itoa(shell->her_index_to_use);
// 			ft_strcpy(shell->heredoc_fname, ".heredoc_");
// 			ft_strcat(shell->heredoc_fname, index_str);
// 			ft_strcat(shell->heredoc_fname, ".txt");
// 			free(index_str);
// 			if (redirect_stdin_to_heredoc(shell->heredoc_fname) == -1)
// 				return (-1);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }

int	setup_redirs_aux(t_token *token, t_minishell *shell)
{
	char	*index_str;

	if (token->type == TOKEN_IN_REDIRECT)
		return (setup_in_redirect(token, shell));
	else if (token->type == TOKEN_OUT_REDIRECT)
		return (setup_out_redirect(token, shell));
	else if (token->type == TOKEN_APPEND_REDIRECT)
		return (setup_append_redirect(token, shell));
	else if (token->type == TOKEN_HEREDOC)
	{
		index_str = ft_itoa(shell->her_index_to_use);
		ft_strcpy(shell->heredoc_fname, ".heredoc_");
		ft_strcat(shell->heredoc_fname, index_str);
		ft_strcat(shell->heredoc_fname, ".txt");
		free(index_str);
		return (redirect_stdin_to_heredoc(shell->heredoc_fname));
	}
	return (0);
}

int	setup_redirections(t_token *token, t_minishell *shell)
{
	while (token && token->type != TOKEN_PIPE)
	{
		if (setup_redirs_aux(token, shell) == -1)
			return (-1);
		token = token->next;
	}
	return (0);
}

/// @brief Redirect input from a file to stdin.
/// @param filename The name of the file to read from.
/// @return 0 on success, -1 on failure.
int	redirect_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_perror(" No such file or directory\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_perror("Failed to duplicate file descriptor\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

//TODO - Forbidden functions
char	*get_dirname(const char *path)
{
	char	*dir_path;
	char	*last_slash;

	dir_path = ft_strdup(path);
	if (dir_path == NULL)
		return (NULL);
	last_slash = ft_strrchr(dir_path, '/');
	if (last_slash != NULL)
	{
		if (last_slash == dir_path)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
	}
	else
		ft_strcpy(dir_path, ".");
	return (dir_path);
}

int	redirect_output(const char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_perror("open\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
