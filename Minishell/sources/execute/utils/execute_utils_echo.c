/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:35 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:36 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Check if the command is an echo command.
/// @param token The head of the token list.
/// @return 1 if the command is echo, 0 otherwise.
int	is_echo_command(t_token *token)
{
	if (token && token->type == TOKEN_IN_REDIRECT
		&& ft_strcmp(token->data, "echo") == 0)
		return (1);
	return (0);
}

/// @brief Remove a token from the token list.
/// @param current Pointer to the current token.
/// @param prev Pointer to the previous token.
/// @param token Pointer to the head of the token list.
/// @return true if the token was removed successfully.
static bool	remove_token(t_token **current, t_token **prev, t_token **token)
{
	t_token	*to_remove;

	to_remove = *current;
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		*token = (*current)->next;
	*current = (*current)->next;
	free(to_remove->data);
	free(to_remove);
	return (true);
}

/// @brief Handle the removal of input redirection tokens.
/// @param params Pointer to the echo parameters structure.
/// @return true if the redirection was handled successfully, false otherwise.
static bool	handle_redirection(t_echo_params *params)
{
	if ((params->current)->next
		&& access((params->current)->next->data, F_OK) == -1)
	{
		params->shell->exit_code = 1;
		ft_perror(" No such file or directory\n");
		return (false);
	}
	if (!remove_token(&(params->current), &(params->prev), params->token))
		return (false);
	if (params->current && ((params->current)->type == TOKEN_DATA
			|| (params->current)->type == TOKEN_ARGUMENT))
	{
		*(params->args_removed) = true;
		return (remove_token(&(params->current), &(params->prev),
				params->token));
	}
	return (true);
}

/// @brief Process the tokens for the echo command, handling input redirections
/// @param params Pointer to the echo parameters structure.
/// @return true if the tokens were processed successfully, false otherwise.
static bool	process_echo_tokens(t_echo_params *params)
{
	while (params->current)
	{
		if (params->current->type == TOKEN_IN_REDIRECT)
		{
			if (!handle_redirection(params))
				return (false);
		}
		else
		{
			if (params->current->type == TOKEN_ARGUMENT
				|| params->current->type == TOKEN_DATA)
				params->has_args = true;
			params->prev = params->current;
			params->current = params->current->next;
		}
	}
	return (true);
}

/// @brief Remove input redirections for the echo command.
/// @param token The head of the token list.
/// @param shell The shell structure.
/// @param args_removed Pointer to a flag indicating if arguments were removed.
/// @return true if successful, false otherwise.
bool	rmv_inputredir_echo(t_token **token, t_minishell *shell,
	bool *args_removed)
{
	t_echo_params	params;

	params.token = token;
	params.shell = shell;
	params.args_removed = args_removed;
	params.current = *token;
	params.prev = NULL;
	params.has_args = false;
	if (!params.current || params.current->type != TOKEN_COMMAND
		|| ft_strcmp(params.current->data, "echo") != 0)
		return (true);
	if (get_next_pipe(params.current))
		return (true);
	if (!process_echo_tokens(&params))
		return (false);
	if (!params.has_args && *(params.args_removed))
	{
		params.shell->exit_code = 1;
		ft_perror(" No such file or directory\n");
		return (false);
	}
	return (true);
}
