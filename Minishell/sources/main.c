/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:24 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:25 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	remove_env_vars(t_minishell *shell)
{
	t_env	*current;
	t_env	*temp;

	while (shell->export_list && is_excluded((shell->export_list)->var))
	{
		temp = shell->export_list;
		shell->export_list = (shell->export_list)->next;
		free(temp->var);
		free(temp);
	}
	current = shell->export_list;
	while (current && current->next)
	{
		if (is_excluded(current->next->var))
		{
			temp = current->next;
			current->next = current->next->next;
			free(temp->var);
			free(temp);
		}
		else
			current = current->next;
	}
}

/// @brief Debug function to print the token list
/// @param token_list 
void	print_token_list(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	printf(YELLOW "Debug display of the Token List:\n" RESET);
	while (current)
	{
		printf(YELLOW "Token: %s, Type: %d\n" RESET, current->data,
			current->type);
		current = current->next;
	}
}

void	remove_heredoc_files(t_minishell *shell)
{
	char	*index_str;

	while (shell->heredoc_index >= 0)
	{
		index_str = ft_itoa(shell->heredoc_index);
		ft_strcpy(shell->heredoc_fname, ".heredoc_");
		ft_strcat(shell->heredoc_fname, index_str);
		ft_strcat(shell->heredoc_fname, ".txt");
		unlink(shell->heredoc_fname);
		free(index_str);
		shell->heredoc_index--;
	}
}

static void	minishell(t_minishell *shell)
{
	char		*line;

	shell->token_list = NULL;
	while (1)
	{
		setup_sig_handle();
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (!is_empty_or_space(line))
		{
			add_history(line);
			if (process_tokens(shell, line))
			{
				if (shell->token_list != NULL)
					execute(shell->token_list, shell);
			}
			remove_heredoc_files(shell);
			free_tokens(shell->token_list);
			shell->token_list = NULL;
		}
		free(line);
	}
}

/// @brief Initializes the env list and export list
////       starts minishell loop and frees the lists in the end
/// @param argv and argc are voided.
/// @param envp reads the system envlist
/// @return 
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env_list = initialize_env(envp, &shell);
	shell.export_list = initialize_env(envp, &shell);
	bubble_sort(&shell);
	remove_env_vars(&shell);
	add_declare(&shell);
	minishell(&shell);
	free_env_list(shell.env_list);
	free_env_list(shell.export_list);
	return (0);
}
