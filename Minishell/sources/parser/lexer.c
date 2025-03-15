/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:34 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:35 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	lexer_helper(t_minishell *shell, char *string)
{
	int			stdout_backup;
	const char	*prefix;
	const char	*suffix;

	prefix = "minishell: syntax error near unexpected token '";
	suffix = "'\n";
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
		ft_perror("dup failed\n");
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		ft_perror("dup2 failed\n");
	write(STDOUT_FILENO, prefix, ft_strlen(prefix));
	write(STDOUT_FILENO, string, ft_strlen(string));
	write(STDOUT_FILENO, suffix, ft_strlen(suffix));
	shell->exit_code = 2;
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		ft_perror("dup2 failed\n");
	close(stdout_backup);
	return (1);
}

int	check_consecutive_tokens(t_minishell *shell, t_token *current, int type1,
	int type2)
{
	if (current->type == type1 || current->type == type2)
	{
		if (current->next && (current->next->type == type1
				|| current->next->type == type2))
			return (lexer_helper(shell, current->next->data));
	}
	return (0);
}

int	ft_lexer(t_minishell *shell)
{
	t_token	*current;
	int		error_code;

	current = shell->token_list;
	while (current)
	{
		error_code = check_consecutive_tokens(shell, current, 3, 3);
		if (error_code != 0)
			return (error_code);
		error_code = check_consecutive_tokens(shell, current, 2, 6);
		if (error_code != 0)
			return (error_code);
		error_code = check_consecutive_tokens(shell, current, 1, 7);
		if (error_code != 0)
			return (error_code);
		error_code = check_consecutive_tokens(shell, current, 5, 5);
		if (error_code != 0)
			return (error_code);
		current = current->next;
	}
	return (0);
}
