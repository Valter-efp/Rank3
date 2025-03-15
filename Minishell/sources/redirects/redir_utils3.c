/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:54 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:55 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	setup_in_redirect(t_token *token, t_minishell *shell)
{
	if (handle_input_redirection(token, shell) == -1)
	{
		shell->exit_code = 1;
		return (-1);
	}
	return (0);
}

int	setup_out_redirect(t_token *token, t_minishell *shell)
{
	if (handle_output_redirection(token) == -1)
	{
		shell->exit_code = 1;
		return (-1);
	}
	return (0);
}

int	setup_append_redirect(t_token *token, t_minishell *shell)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_APPEND_REDIRECT)
	{
		if (handle_append_redirection(current) == -1)
		{
			shell->exit_code = 1;
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

// int	setup_heredoc_redirect(t_token *token, t_minishell *shell)
// {
// 	if (handle_heredoc(token) == -1)
// 	{
// 		shell->exit_code = 1;
// 		return (-1);
// 	}
// 	return (0);
// }

// int setup_heredoc_redirect(t_token *token, t_minishell *shell)
// {
//     if (handle_heredoc(token, shell->heredoc_index) == -1)
//     {
//         shell->exit_code = 1;
//         return (-1);
//     }
//     shell->heredoc_index++; // Increment heredoc_index after handling
//     return (0);
// }

// int setup_heredoc_redirect(t_token *token, t_minishell *shell)
// {
//     char heredoc_fname[64];
//     if (handle_heredoc(token, shell->heredoc_index, heredoc_fname) == -1)
//     {
//         shell->exit_code = 1;
//         return (-1);
//     }
//     shell->heredoc_index++; // Increment heredoc_index after handling
//     return (0);
// }

int	setup_heredoc_redirect(t_token *token, t_minishell *shell)
{
	shell->heredoc_index++;
	if (handle_heredoc(token, shell->heredoc_index, shell) == -1)
	{
		shell->exit_code = 1;
		return (-1);
	}
	return (0);
}
