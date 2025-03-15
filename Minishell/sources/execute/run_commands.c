/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:08 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:09 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

extern char	**environ;

/// @brief Check if a command is a built-in command.
/// @param cmd The command to check.
/// @return 1 if the command is a built-in command, 0 otherwise.
int	is_builtin_command(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}

/// @brief Execute a command by searching through the directories in the PATH.
/// @param cmd The command to execute.
/// @param args The arguments for the command.
/// @param path_dirs The directories in the PATH.
void	execute_command(char *cmd, char **args, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = malloc(ft_strlen(path_dirs[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
		{
			ft_perror("minishell: ");
			ft_perror(cmd);
			ft_perror(": command not found");
			exit(EXIT_FAILURE);
		}
		ft_strcpy(full_path, path_dirs[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		execve(full_path, args, environ);
		free(full_path);
		i++;
	}
}

void	run_builtin_cmds(char **args, t_minishell *sh, t_token *tkn_lst)
{
	t_token	*last_path;
	int		argc;

	last_path = get_last_relevant_path(tkn_lst);
	argc = 0;
	while (args[argc])
		argc++;
	if (last_path)
		args[--argc] = last_path->data;
	if (!ft_strcmp(args[0], "echo"))
		sh->exit_code = ft_echo(args, sh->exit_code);
	else if (!ft_strcmp(args[0], "exit"))
		sh->exit_code = ft_exit(args, sh->env_list, sh->export_list, tkn_lst);
	else if (!ft_strcmp(args[0], "cd"))
		sh->exit_code = ft_cd(args);
	else if (!ft_strcmp(args[0], "pwd"))
		sh->exit_code = ft_pwd();
	else if (!ft_strcmp(args[0], "env"))
		sh->exit_code = ft_env(sh->env_list);
	else if (!ft_strcmp(args[0], "export"))
		sh->exit_code = ft_export(args, sh);
	else if (!ft_strcmp(args[0], "unset"))
		sh->exit_code = ft_unset(args, &(sh->export_list), &(sh->env_list));
	else
		sh->exit_code = 127;
}

/// @brief Run the commands by checking if they are built-in or native comds.
/// @param args The arguments for the command.
/// @param env_list The environment list.
/// @param export_list The export list.
/// @param token_list The token list.
void	run_commands(char **args, t_minishell *shell, t_token *token_list)
{
	if (is_builtin_command(args[0]))
		run_builtin_cmds(args, shell, token_list);
	else
		run_native_cmds(args, shell);
	if (shell->exit_code == 127)
	{
		ft_perror("minishell: ");
		ft_perror(args[0]);
		ft_perror(": command not found\n");
	}
}
