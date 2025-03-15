/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:30 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:31 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

volatile sig_atomic_t	g_signal_flag = 0; // Global flag to handle SIGINT

/// CTRL + C Handler for heredoc
/// @brief When SIGINT is received, sets the global flag to stop heredoc read.
/// @param signo The signal number.
void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	g_signal_flag = 1;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close (STDIN_FILENO);
}

void	sigint_handler(int signo)
{
	(void)signo;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/// Setup the signal handlers for general use (Ctrl+C)
void	setup_sig_handle(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGPIPE, SIG_IGN);
}

/// Setup the signal handlers for heredoc mode (handling Ctrl+C)
void	setup_sig_handle_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sigint_handler_heredoc);
}

void	setup_sig_handle_child(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGPIPE, SIG_DFL);
}
