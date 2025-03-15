/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:18 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:19 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Creates a new token and initializes it.
/// @param data the string data of the token.
/// @param index Token type index.
/// @return 
t_token	*create_token(const char *data, int index)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = ft_strdup(data);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = determine_token_type(data, index);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/// @brief Determines the token type.
/// @param data The string data of the token.
/// @param index Token type index.
/// @return 
int	determine_token_type(const char *data, int index)
{
	if (ft_strcmp(data, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(data, "<") == 0)
		return (TOKEN_IN_REDIRECT);
	if (ft_strcmp(data, ">") == 0)
		return (TOKEN_OUT_REDIRECT);
	if (ft_strcmp(data, ">>") == 0)
		return (TOKEN_APPEND_REDIRECT);
	if (ft_strcmp(data, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (index == 0)
		return (TOKEN_COMMAND);
	else
		return (TOKEN_ARGUMENT);
}

/// @brief Adds a new token to the end of the list.
/// @param head Ptr to the head of the list. Update if list is empty
/// @param current Ptr to the current token in the list.
/// @param data Ptr to the string associated with the new token.
/// @param type An int representing the type of token.
void	add_token(t_token **head, t_token **current, char *data, int type)
{
	t_token	*new_token;

	new_token = create_token(data, type);
	if (!new_token)
		return ;
	new_token->type = type;
	new_token->next = NULL;
	if (!(*head))
	{
		*head = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		new_token->prev = *current;
		*current = new_token;
	}
}

/// @brief Frees all the tokens in the list.
/// @param head Ptr to the head of the list.
void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next_token;

	current = head;
	while (current != NULL)
	{
		next_token = current->next;
		free(current->data);
		free(current);
		current = next_token;
	}
}

/// @brief Adds a token from the input to the token list.
/// First check for redirs and pipes, then expand the token.
/// @param args The token arguments structure.
/// @param token The input token string.
void	add_token_from_input(t_token_args *args, char *token,
	t_minishell *shell)
{
	char	*data;

	if (ft_strcmp(token, "<") == 0)
		add_token(args->head, args->current, token, TOKEN_IN_REDIRECT);
	else if (ft_strcmp(token, ">") == 0)
		add_token(args->head, args->current, token, TOKEN_OUT_REDIRECT);
	else if (ft_strcmp(token, ">>") == 0)
		add_token(args->head, args->current, token, TOKEN_APPEND_REDIRECT);
	else if (ft_strcmp(token, "|") == 0)
		add_token(args->head, args->current, token, TOKEN_PIPE);
	else if (ft_strcmp(token, "<<") == 0)
		add_token(args->head, args->current, token, TOKEN_HEREDOC);
	else
	{
		data = handle_token_with_expansions(token, shell);
		if (!data)
			return ;
		if (args->head && !(*args->head))
			add_token(args->head, args->current, data, TOKEN_COMMAND);
		else
			add_token(args->head, args->current, data, TOKEN_ARGUMENT);
		free(data);
	}
}
