/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:04 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:05 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Print an error message to the standard error.
/// @param msg The error message to print.
void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

/// @brief Print an error message with an argument to the standard error.
/// @param prefix The prefix of the error message.
/// @param arg The argument to include in the error message.
/// @param suffix The suffix of the error message.
void	print_error_with_arg(const char *prefix, const char *arg,
			const char *suffix)
{
	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

/// @brief Change the current working directory.
/// @param args The list of args, where the first arg is the target dir.
/// @return 0 on success, 1 on failure.
int	ft_cd(char **args)
{
	char	*home;

	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		home = getenv("HOME");
		if (!home || chdir(home) != 0)
		{
			ft_perror("minishell: cd\n");
			return (1);
		}
		return (0);
	}
	if (args[2])
	{
		print_error("minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		print_error_with_arg
			("minishell: cd: ", args[1], ": No such file or directory\n");
		return (1);
	}
	return (0);
}
