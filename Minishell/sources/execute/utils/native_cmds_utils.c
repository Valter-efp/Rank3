/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:26 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:27 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

static void	r_n_c_handle_child(char **args, t_minishell *shell)
{
	int	ret;

	ret = r_handle_child_process(args, shell);
	free_tokens(shell->token_list);
	shell->token_list = NULL;
	free_env_list(shell->env_list);
	free_env_list(shell->export_list);
	exit(ret);
}

static void	r_n_c_update_exit_code(t_minishell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = 1;
}

int	run_native_cmds(char **args, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_sig_handle_child();
		r_n_c_handle_child(args, shell);
	}
	else if (pid < 0)
	{
		ft_perror("fork\n");
		shell->exit_code = 1;
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		r_n_c_update_exit_code(shell, status);
	}
	return (shell->exit_code);
}

/// @brief Get all directories from the PATH environment variable.
/// @param path_env The PATH environment variable.
/// @return An array of directories, or NULL on failure.
char	**get_all_dirs(char *path_env)
{
	char	**path_dirs;
	char	**all_dirs;
	int		i;

	path_dirs = ft_split(path_env, ':');
	all_dirs = malloc((ft_strarrlen(path_dirs) + 2) * sizeof(char *));
	if (!all_dirs)
	{
		ft_perror("minishell\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (path_dirs[i])
	{
		all_dirs[i] = path_dirs[i];
		i++;
	}
	all_dirs[i] = ft_strdup(".");
	all_dirs[i + 1] = NULL;
	free(path_dirs);
	return (all_dirs);
}

/// @brief Wait for a child process to finish.
/// @param pid The process ID of the child process.
void	wait_for_child_process(pid_t pid)
{
	int	status;

	while (1)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			break ;
	}
}
