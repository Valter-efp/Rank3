/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:21 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:22 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	is_empty_string(const char *str)
{
	return (str && str[0] == '\0');
}

void	clean_list(t_token **token_list)
{
	t_token	*current;
	t_token	*prev;
	t_token	*to_delete;

	current = *token_list;
	prev = NULL;
	while (current)
	{
		if (is_empty_string(current->data))
		{
			to_delete = current;
			if (prev)
				prev->next = current->next;
			else
				*token_list = current->next;
			current = current->next;
			free(to_delete->data);
			free(to_delete);
			continue ;
		}
		prev = current;
		current = current->next;
	}
}

/// @brief Processes the tokens from the input line and creates a token list.
/// @param token_list The list of tokens to be populated.
/// @param line The input line to be processed.
/// @param env_list The environment variable list.
int	process_tokens(t_minishell *shell, char *line)
{
	shell->heredoc_index = -1;
	shell->her_index_to_use = 0;
	shell->token_list = make_command_tokens(line, shell);
	if (!(shell->token_list))
		return (1);
	clean_list(&shell->token_list);
	if (!(shell->token_list))
		return (1);
	if (shell->token_list->type == 4)
		shell->token_list->type = 0;
	if (ft_lexer(shell))
		return (0);
	return (1);
}

/// @brief Processes a single token, expanding it if necessary.
/// @param token The input token string.
/// @param env_list The environment variable list.
/// @param i The current index in the token string.
/// @return The expanded token string.
char	*process_token(const char *token, t_minishell *shell, size_t *i)
{
	char	*expanded_seg;
	char	quote;

	if (token[*i] == '\'' || token[*i] == '"')
	{
		quote = token[(*i)++];
		expanded_seg = expand_segment(token, shell, i, quote);
	}
	else
		expanded_seg = expand_segment(token, shell, i, 0);
	return (expanded_seg);
}

/// @brief Creates a list of command tokens from the input string.
/// @param input The input string.
/// @param env_list The environment variable list.
/// @return The head of the token list.
t_token	*make_command_tokens(const char *input, t_minishell *shell)
{
	t_token			*head;
	t_token			*current;
	char			**split_input;
	t_token_args	args;
	int				i;

	head = NULL;
	current = NULL;
	split_input = split_command_line(input);
	args.head = &head;
	args.current = &current;
	args.env_list = shell->env_list;
	i = 0;
	if (!split_input)
		return (NULL);
	while (split_input[i])
	{
		if (!process_single_input(&args, split_input[i++], shell))
		{
			free_split_input(split_input);
			return (NULL);
		}
	}
	free_split_input(split_input);
	return (head);
}
