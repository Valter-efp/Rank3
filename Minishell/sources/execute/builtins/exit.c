/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:55 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:56 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Inits the cleanup data structure environment, export, token lists.
/// @param data The cleanup data structure to initialize.
/// @param env_list The environment list to set.
/// @param export_list The export list to set.
/// @param token_list The token list to set.
void	init_cleanup_lists(t_cleanup_data *data, t_env *env_list,
		t_env *export_list, t_token *token_list)
{
	data->env_list = env_list;
	data->export_list = export_list;
	data->token_list = token_list;
}

/// @brief Initialize the cleanup data structure with arguments.
/// @param data The cleanup data structure to initialize.
/// @param args The arguments to set.
void	init_cleanup_args(t_cleanup_data *data, char **args)
{
	data->args = args;
}

/// @brief Perform cleanup of allocated resources and exit with the given code.
/// @param exit_code The exit code to return.
/// @param data The cleanup data structure containing resources to free.
/// @return The exit code (this line is never reached).
int	exit_cleanup(int exit_code, t_cleanup_data *data)
{
	int	i;

	if (data->env_list)
		free_env_list(data->env_list);
	if (data->export_list)
		free_env_list(data->export_list);
	if (data->token_list)
		free_tokens(data->token_list);
	if (data->args)
	{
		i = 0;
		while (data->args[i] != NULL)
		{
			free(data->args[i]);
			i++;
		}
		free(data->args);
	}
	rl_clear_history();
	exit(exit_code);
	return (exit_code);
}

/// @brief Print an error message and perform cleanup.
/// @param data The cleanup data structure.
/// @param msg The error message to print.
/// @param arg The argument to include in the message (optional).
/// @param exit_code The exit code to use for cleanup.
static void	handle_exit_err(t_cleanup_data *data, const char *msg,
		const char *arg, int exit_code)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit_cleanup(exit_code, data);
}

/// @brief Handle the exit command, performing cleanup and exiting the shell.
/// @param args The list of args, where the first argument may be an exit code.
/// @param env_list The environment list to clean up.
/// @param export_list The export list to clean up.
/// @param token_list The token list to clean up.
/// @return This function does not return as it calls exit().
int	ft_exit(char **args, t_env *env_list, t_env *export_list,
		t_token *token_list)
{
	t_cleanup_data	data;
	long long		exit_code;
	int				error;

	init_cleanup_lists(&data, env_list, export_list, token_list);
	init_cleanup_args(&data, args);
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (args[1] && !ft_is_numeric_argument(args[1]))
		handle_exit_err(&data, ": numeric argument required\n", args[1], 2);
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (args[1])
	{
		exit_code = ft_safe_atoi(args[1], &error);
		if (error)
			handle_exit_err(&data, ": numeric argument required\n", args[1], 2);
	}
	else
		exit_code = 0;
	exit_cleanup(exit_code, &data);
	return (exit_code);
}
