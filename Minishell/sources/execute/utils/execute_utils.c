/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:32 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:33 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Count the number of argument tokens in the token list.
/// @param list The head of the token list.
/// @return The number of argument tokens.
int	count_args(t_token *list)
{
	int		count;
	t_token	*buf;

	count = 1;
	buf = list->next;
	while (buf && buf->type == TOKEN_ARGUMENT)
	{
		count++;
		buf = buf->next;
	}
	return (count);
}

/// @brief Initialize an array of strings to hold the arguments.
/// @param size The number of arguments.
/// @return A pointer to the initialized array of strings, or NULL on failure.
char	**initialize_args(int size)
{
	char	**args;
	int		j;

	args = malloc(sizeof(char *) * (size + 2));
	if (!args)
		return (NULL);
	j = 0;
	while (j < size + 2)
		args[j++] = NULL;
	return (args);
}

void	fill_args(char **args, t_token *list)
{
	t_token	*buf;
	int		i;

	i = 0;
	buf = list;
	while (buf && buf->type != TOKEN_PIPE)
	{
		if (buf->type == TOKEN_COMMAND || buf->type == TOKEN_ARGUMENT)
		{
			args[i] = malloc(sizeof(char) * (ft_strlen(buf->data) + 1));
			if (args[i])
				ft_strlcpy(args[i++], buf->data, ft_strlen(buf->data) + 1);
		}
		else if (buf->type == TOKEN_IN_REDIRECT
			|| buf->type == TOKEN_OUT_REDIRECT
			|| buf->type == TOKEN_APPEND_REDIRECT
			|| buf->type == TOKEN_HEREDOC)
			buf = buf->next;
		buf = buf->next;
	}
	args[i] = NULL;
}

/// @brief Copy a double pointer string array to another double pointer.
/// @param ambient The destination double pointer.
/// @param envp The source double pointer string array.
void	copy_double_pointer(char ***ambient, char **envp)
{
	char	**buf;

	if (!envp)
	{
		*ambient = 0;
		return ;
	}
	buf = malloc(sizeof(char *) * ft_strlen_double((const char **)envp) + 1);
	if (!buf)
	{
		*ambient = 0;
		return ;
	}
	*ambient = buf;
	while (*envp)
	{
		*buf = ft_strdup(*envp);
		envp++;
		buf++;
	}
	*buf = NULL;
	return ;
}

/// @brief Clean up the arguments array by freeing allocated memory.
/// @param args The array of arguments to clean up.
void	cleanup_args(char **args)
{
	int	j;

	j = 0;
	while (args[j] != NULL)
		free(args[j++]);
	free(args);
}
