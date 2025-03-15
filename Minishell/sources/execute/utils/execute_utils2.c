/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:29 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:30 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Executes a command, handling arguments for built-in and native comds
/// @param current_command Pointer to the current command token.
/// @param env_list Pointer to the environment variable list.
/// @param export_list Pointer to the export list.
int	run_commands_with_args(t_token *current_command, t_minishell *shell)
{
	char	**args;
	int		arg_count;
	int		ret;

	ret = 0;
	arg_count = count_args(current_command);
	args = initialize_args(arg_count);
	if (!args)
	{
		ft_perror("initialize_args\n");
		return (1);
	}
	fill_args(args, current_command);
	if (args[0] && is_builtin_command(args[0]))
	{
		run_builtin_cmds(args, shell, current_command);
		ret = shell->exit_code;
	}
	else if (args[0])
	{
		ret = run_native_cmds(args, shell);
		shell->exit_code = ret;
	}
	cleanup_args(args);
	return (ret);
}

/// @brief Finds the next pipe token in the list.
/// @param token The current token.
/// @return A pointer to the next pipe token, or NULL if none exists.
t_token	*get_next_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/// @brief Moves to the next command in the token list after a pipe.
/// @param token The current token.
/// @return A pointer to the next command token, or NULL if none exists.
t_token	*get_next_command(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}

void	handle_builtin_cmds(t_token *current_command, t_minishell *shell,
		t_token *list)
{
	int		arg_count;
	char	**args;

	arg_count = count_args(current_command);
	args = initialize_args(arg_count);
	if (!args)
	{
		ft_perror("initialize_args\n");
		return ;
	}
	fill_args(args, current_command);
	run_builtin_cmds(args, shell, list);
	cleanup_args(args);
}

void	wait_for_children(t_minishell *shell, pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		exit_code;
	int		signal_code;

	while (true)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (pid == last_pid)
				shell->exit_code = exit_code;
		}
		else if (WIFSIGNALED(status))
		{
			signal_code = WTERMSIG(status);
			if (pid == last_pid)
				shell->exit_code = 128 + signal_code;
		}
	}
}
