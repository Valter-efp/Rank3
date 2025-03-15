/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:42 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:43 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Allocate memory and gets the current working directory.
/// @param size The initial size of the buffer to allocate.
/// @return A ptr to the buffer containing the WD, or NULL.
static char	*expand_buffer(char *buf, size_t *size)
{
	char	*new_buf;

	*size *= 2;
	new_buf = (char *)malloc(*size);
	if (!new_buf)
	{
		free(buf);
		printf("minishell: pwd: allocation error\n");
		return (NULL);
	}
	ft_strcpy(new_buf, buf);
	free(buf);
	return (new_buf);
}

static char	*allocate_and_get_cwd(size_t size)
{
	char	*buf;

	buf = (char *)malloc(size);
	if (!buf)
	{
		printf("minishell: pwd: allocation error\n");
		return (NULL);
	}
	while (!getcwd(buf, size))
	{
		if (errno != ERANGE)
		{
			free(buf);
			printf("minishell: pwd: error retrieving current directory\n");
			return (NULL);
		}
		buf = expand_buffer(buf, &size);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

/// @brief Print the current working directory to the standard output.
/// @return 0 on success, 1 on failure.
int	ft_pwd(void)
{
	char	*buf;

	buf = allocate_and_get_cwd(1024);
	if (!buf)
		return (1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
