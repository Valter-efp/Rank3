/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:03 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:04 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Get the last redirection token of a specified type.
/// @param token The head of the token list.
/// @param type The type of redirection token to search for.
/// @return The last redirection token of the specified type, or NULL if not.
t_token	*get_last_redirection_token(t_token *token, int type)
{
	t_token	*last_token;

	last_token = NULL;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == type)
			last_token = token;
		token = token->next;
	}
	return (last_token);
}

/// @brief Get the last relevant path token in the token list.
/// @param token The head of the token list.
/// @return The last relevant path token, or NULL if not found.
t_token	*get_last_relevant_path(t_token *token)
{
	t_token	*last_path;

	last_path = NULL;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_ARGUMENT)
			last_path = token;
		else if (token->type == TOKEN_COMMAND
			&& (ft_strcmp(token->data, "grep") != 0
				&& ft_strcmp(token->data, "cat") != 0))
			break ;
		else if (token->type == TOKEN_PIPE
			|| token->type == TOKEN_IN_REDIRECT
			|| token->type == TOKEN_OUT_REDIRECT
			|| token->type == TOKEN_APPEND_REDIRECT
			|| token->type == TOKEN_HEREDOC)
			break ;
		token = token->next;
	}
	return (last_path);
}

/// @brief Handle input redirection by setting up the file dscrptrs
/// @param token The head of the token list.
/// @param env_list The environment list.
/// @return 0 on success, -1 on failure.
int	handle_input_redirection(t_token *token, t_minishell *shell)
{
	t_token	*last_token;
	t_token	*last_path;

	last_token = get_last_redirection_token(token, TOKEN_IN_REDIRECT);
	if (!last_token)
	{
		shell->exit_code = 2;
		ft_perror(" No redirection token found\n");
		return (-1);
	}
	last_path = get_last_relevant_path(last_token->next);
	if (!last_path)
	{
		shell->exit_code = 2;
		ft_perror(" No such file or directory\n");
		return (-1);
	}
	if (redirect_input(last_path->data) == -1)
	{
		shell->exit_code = 1;
		return (-1);
	}
	return (0);
}

int	handle_output_redirection(t_token *token)
{
	int		fd;
	char	*path;

	if (!token || !token->next)
		return (-1);
	path = token->next->data;
	if (check_directory(path) == -1)
		return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			permission_denied_error(path);
		else
			n_f_o_d_error(path);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_append_redirection(t_token *token)
{
	int		fd;
	char	*path;

	if (!token || !token->next)
		return (-1);
	path = token->next->data;
	if (check_directory(path) == -1)
		return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			permission_denied_error(path);
		else
			n_f_o_d_error(path);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		redirect_output_error(path);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
