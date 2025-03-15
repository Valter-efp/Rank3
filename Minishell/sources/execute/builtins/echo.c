/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:00 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:01 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Print the argument to the standard output, handling special cases.
/// @param arg The argument to print.
/// @param last_exit_code The last exit code to print if the argument is "$?".
void	print_arg(char *arg, int last_exit_code)
{
	size_t	len;
	char	*exit_code_str;

	if (ft_strncmp(arg, "$?", 2) == 0 && ft_strlen(arg) == 2)
	{
		exit_code_str = ft_itoa(last_exit_code);
		if (exit_code_str)
		{
			write(1, exit_code_str, ft_strlen(exit_code_str));
			free(exit_code_str);
		}
	}
	else
	{
		len = ft_strlen(arg);
		write(1, arg, len);
	}
}

void	jump_n(char ***args, int *newline)
{
	int	i;

	while ((*args)[0] && !ft_strncmp((*args)[0], "-n", 2))
	{
		i = 1;
		while ((*args)[0][i] == 'n')
			i++;
		if ((*args)[0][i] == '\0')
		{
			(*args)++;
			*newline = 0;
		}
		else
			break ;
	}
}

/// @brief Echo the given arguments to the standard output.
/// @param args The list of arguments to echo.
/// @return 0 on success.
int	ft_echo(char **args, int last_exit_code)
{
	int	newline;

	newline = 1;
	if (!args || !*args)
		return (1);
	args++;
	jump_n(&args, &newline);
	while (args[0])
	{
		print_arg(args[0], last_exit_code);
		args++;
		if (args[0])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
