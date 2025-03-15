/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:50 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:51 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	n_f_o_d_error(char *path)
{
	ft_perror("minishell: ");
	ft_perror(path);
	ft_perror(": No such file or directory\n");
}

void	permission_denied_error(char *path)
{
	ft_perror("minishell: ");
	ft_perror(path);
	ft_perror(": Permission denied\n");
}

void	redirect_output_error(char *path)
{
	ft_perror("minishell: ");
	ft_perror(path);
	ft_perror(": Error redirecting output\n");
}
