/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:23 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:24 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

static int	e_c_i_p_execute_path(char *path, char **args, char **envp)
{
	int	ret;

	ret = do_command(path, args, envp);
	free(path);
	return (ret);
}

static void	e_c_i_p_handle_error(char **args)
{
	int	i;

	ft_perror("minishell: ");
	ft_perror(args[0]);
	ft_perror(": command not found\n");
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	execute_command_in_path(char **args, char **envp, char **path_dirs)
{
	char	*full_path;
	int		i;
	int		ret;

	i = 0;
	ret = 127;
	while (path_dirs[i])
	{
		if (args[0][0] == '/' || args[0][0] == '.')
			full_path = args[0];
		else
			full_path = make_full_path(path_dirs[i], args[0]);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
			return (e_c_i_p_execute_path(full_path, args, envp));
		free(full_path);
		i++;
	}
	e_c_i_p_handle_error(args);
	return (ret);
}

char	*make_full_path(const char *dir, const char *command)
{
	char	*full_path;

	full_path = malloc(ft_strlen(dir) + ft_strlen(command) + 2);
	if (!full_path)
	{
		ft_perror("minishell\n");
		return (NULL);
	}
	ft_strlcpy(full_path, dir, ft_strlen(dir) + 1);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (full_path);
}

int	do_command(const char *full_path, char **args, char **envp)
{
	if (execve(full_path, args, envp) == -1)
	{
		if (errno == EACCES)
		{
			ft_perror("minishell: ");
			ft_perror(args[0]);
			ft_perror(": command not found\n");
			return (127);
		}
		else if (errno == ENOENT)
		{
			ft_perror(" No such file or directory\n");
			return (127);
		}
		else
		{
			ft_perror("execve\n");
			return (127);
		}
	}
	return (0);
}
