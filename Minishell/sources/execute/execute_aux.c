/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:13 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:14 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// int	handle_child(t_execution_data *data, t_token *current_command,
// 	t_minishell *shell)
// {
// 	int	ret;

// 	if (data->input_fd != STDIN_FILENO)
// 	{
// 		dup2(data->input_fd, STDIN_FILENO);
// 		close(data->input_fd);
// 	}
// 	if (!data->is_last_command)
// 	{
// 		close(data->pipe_fds[0]);
// 		dup2(data->pipe_fds[1], STDOUT_FILENO);
// 		close(data->pipe_fds[1]);
// 	}
// 	if (setup_redirections(current_command, shell) == -1)
// 		return (shell->exit_code);
// 	if (!current_command->data || current_command->data[0] == '\0')
// 		return (0);
// 	ret = run_commands_with_args(current_command, shell);
// 	shell->exit_code = ret;
// 	return (shell->exit_code);
// }

// static int	redirect_stdin_to_heredoc(const char *filename)
// {
// 	int	fd;

// 	//debug print
// 	write(1, "Redirecting stdin to heredoc\n", 30);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_perror("open\n");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		ft_perror("dup2\n");
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }

int	handle_child(t_execution_data *data, t_token *current_command,
	t_minishell *shell)
{
	int	ret;

	if (data->input_fd != STDIN_FILENO)
		dup2(data->input_fd, STDIN_FILENO);
	if (!data->is_last_command)
	{
		close(data->pipe_fds[0]);
		dup2(data->pipe_fds[1], STDOUT_FILENO);
	}
	if (setup_redirections(current_command, shell) == -1)
		return (shell->exit_code);
	if (!current_command->data || current_command->data[0] == '\0')
		return (0);
	ret = run_commands_with_args(current_command, shell);
	shell->exit_code = ret;
	return (shell->exit_code);
}

int	handle_parent(t_execution_data *data, pid_t pid)
{
	data->last_pid = pid;
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	if (!data->is_last_command)
	{
		close(data->pipe_fds[1]);
		data->input_fd = data->pipe_fds[0];
	}
	return (0);
}

int	fork_and_redirect(t_execution_data *data, t_token *current_command,
	t_minishell *shell)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
	{
		ft_perror("fork\n");
		restore_original_fds(data->original_stdin, data->original_stdout);
		return (-1);
	}
	if (pid == 0)
	{
		setup_sig_handle_child();
		ret = (handle_child(data, current_command, shell));
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free_env_list(shell->env_list);
		free_env_list(shell->export_list);
		exit (ret);
	}
	else
	{
		shell->her_index_to_use++;
		return (handle_parent(data, pid));
	}
}

int	handle_builtin(t_execution_data *data, t_token *current_command,
	t_minishell *shell, t_token *list)
{
	if (is_builtin_command(current_command->data)
		&& !get_next_pipe(current_command))
	{
		if (setup_redirections(current_command, shell) == -1)
		{
			restore_original_fds(data->original_stdin, data->original_stdout);
			return (-1);
		}
		handle_builtin_cmds(current_command, shell, list);
		restore_original_fds(data->original_stdin, data->original_stdout);
		return (1);
	}
	return (0);
}

int	handle_pipe_and_fork(t_execution_data *data, t_token *current_command,
	t_minishell *shell)
{
	if (!data->is_last_command && pipe(data->pipe_fds) == -1)
	{
		ft_perror("pipe\n");
		restore_original_fds(data->original_stdin, data->original_stdout);
		return (-1);
	}
	if (fork_and_redirect(data, current_command, shell) == -1)
	{
		restore_original_fds(data->original_stdin, data->original_stdout);
		return (-1);
	}
	return (0);
}
