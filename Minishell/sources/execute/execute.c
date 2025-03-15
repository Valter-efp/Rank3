/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:11 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:12 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

bool	is_path(const char *command)
{
	return (command[0] == '/' || ft_strncmp(command, "./", 2) == 0
		|| ft_strchr(command, '/') != NULL);
}

bool	check_command(t_token *current_command, t_minishell *shell,
	struct stat *statbuf)
{
	shell->statbuf = statbuf;
	if (!current_command->data || current_command->data[0] == '\0')
	{
		shell->exit_code = 0;
		return (false);
	}
	if (is_path(current_command->data))
	{
		if (stat(current_command->data, statbuf) != 0)
			return ((ft_perror(" No such file or directory\n"),
					shell->exit_code = 127, false));
		if (S_ISDIR(statbuf->st_mode))
			return ((ft_perror(" Is a directory\n"),
					shell->exit_code = 126, false));
		if (access(current_command->data, X_OK) != 0)
			return ((ft_perror(" Permission denied\n"),
					shell->exit_code = 126, false));
	}
	return (true);
}

int	init_execution_data(t_execution_data *data)
{
	data->input_fd = STDIN_FILENO;
	data->last_pid = -1;
	data->is_last_command = false;
	data->args_removed = false;
	if (save_original_fds(&data->original_stdin, &data->original_stdout) == -1)
		return (-1);
	return (0);
}

// void	execute(t_token *list, t_minishell *shell)
// {
// 	t_token				*crnt_cmd;
// 	t_execution_data	data;

// 	signal(SIGPIPE, SIG_IGN);
// 	crnt_cmd = list;
// 	if (init_execution_data(&data) == -1)
// 		return ;
// 	ft_heredocmanage(list, shell);
// 	while (crnt_cmd)
// 	{
// 		if (!check_command(crnt_cmd, shell, &data.statbuf)
// 			|| (crnt_cmd && ft_strcmp(crnt_cmd->data, "echo") == 0
// 				&& !rmv_inputredir_echo(&crnt_cmd, shell, &data.args_removed)))
// 		{
// 			crnt_cmd = get_next_command(crnt_cmd);
// 			continue ;
// 		}
// 		data.is_last_command = (get_next_pipe(crnt_cmd) == NULL);
// 		if (handle_builtin(&data, crnt_cmd, shell, list))
// 			return ;
// 		if (handle_pipe_and_fork(&data, crnt_cmd, shell) == -1)
// 			return ;
// 		crnt_cmd = get_next_command(crnt_cmd);
// 	}
// 	restore_original_fds(data.original_stdin, data.original_stdout);
// 	wait_for_children(shell, data.last_pid);
// }

int	should_skip_command(t_token **crnt_cmd, t_minishell *shell,
	struct stat *statbuf, bool *args_removed)
{
	if (!check_command(*crnt_cmd, shell, statbuf)
		|| (ft_strcmp((*crnt_cmd)->data, "echo") == 0
			&& !rmv_inputredir_echo(crnt_cmd, shell, args_removed)))
	{
		*crnt_cmd = get_next_command(*crnt_cmd);
		return (1);
	}
	return (0);
}

void	execute(t_token *list, t_minishell *shell)
{
	t_token				*crnt_cmd;
	t_execution_data	data;

	signal(SIGPIPE, SIG_IGN);
	crnt_cmd = list;
	if (init_execution_data(&data) == -1)
		return ;
	ft_heredocmanage(list, shell);
	while (crnt_cmd)
	{
		if (should_skip_command(&crnt_cmd, shell, &data.statbuf,
				&data.args_removed))
			continue ;
		data.is_last_command = (get_next_pipe(crnt_cmd) == NULL);
		if (handle_builtin(&data, crnt_cmd, shell, list))
			return ;
		if (handle_pipe_and_fork(&data, crnt_cmd, shell) == -1)
			return ;
		crnt_cmd = get_next_command(crnt_cmd);
	}
	restore_original_fds(data.original_stdin, data.original_stdout);
	wait_for_children(shell, data.last_pid);
}
