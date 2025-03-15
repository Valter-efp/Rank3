/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:16 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:25 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

//Includes
# include <string.h>
# include <fcntl.h>
# include <curses.h>
# include <termcap.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/GNL/get_next_line_bonus.h"
# include "execute.h"
# include "parse.h"
# include "expander.h"
# include "redirects.h"

// Color definitions for printf
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

extern volatile sig_atomic_t	g_signal_flag;

//Main_utils
int		is_empty_or_space(const char *line);
void	bubble_sort(t_minishell *shell);
void	add_declare(t_minishell *shell);
void	initialize_shell(void);
int		is_excluded(char *var_name);
void	print_token_list(t_token *token_list);

//Signals
void	sigint_handler(int signo);
void	setup_sig_handle(void);
void	sigint_handler_heredoc(int signo);
void	setup_sig_handle_heredoc(void);
void	setup_sig_handle_child(void);	

//Signals
void	sigint_handler(int signo);
void	setup_sig_handle(void);
#endif