/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:21 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:22 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

static int	r_h_c_p_prepare(char ***envp, char ***path_dirs, t_minishell *shell)
{
	char	*path_env;

	*envp = env_list_to_array(shell->env_list);
	path_env = getenv("PATH");
	if (!path_env)
	{
		ft_perror("minishell\n");
		free(*envp);
		return (127);
	}
	*path_dirs = get_all_dirs(path_env);
	return (0);
}

static void	r_h_c_p_cleanup(char **envp, char **path_dirs)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	i = 0;
	while (path_dirs[i])
		free(path_dirs[i++]);
	free(path_dirs);
}

int	r_handle_child_process(char **args, t_minishell *shell)
{
	char	**envp;
	char	**path_dirs;
	int		ret;

	ret = r_h_c_p_prepare(&envp, &path_dirs, shell);
	if (ret != 0)
		return (ret);
	ret = execute_command_in_path(args, envp, path_dirs);
	r_h_c_p_cleanup(envp, path_dirs);
	return (ret);
}
