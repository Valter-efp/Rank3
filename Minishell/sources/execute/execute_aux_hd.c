/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_aux_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:16 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:17 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_count_heredocs(t_token *list)
{
	int		i;
	t_token	*cmd;

	cmd = list;
	i = 0;
	while (cmd)
	{
		if (cmd->type == TOKEN_HEREDOC)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

t_token	*get_next_heredoc(t_token *cmd)
{
	cmd = cmd->next;
	while (cmd && cmd->type != TOKEN_HEREDOC)
		cmd = cmd->next;
	return (cmd);
}

int	ft_heredocmanage(t_token *list, t_minishell *shell)
{
	int		i;
	t_token	*cmd;

	cmd = list;
	i = 0;
	i = ft_count_heredocs(list);
	if (cmd->type != TOKEN_HEREDOC)
		cmd = get_next_heredoc(cmd);
	while (i > 0)
	{
		if (setup_heredoc_redirect(cmd, shell) == -1)
			return (-1);
		i--;
		cmd = get_next_heredoc(cmd);
	}
	return (0);
}
