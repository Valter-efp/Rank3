/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:31 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:33 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

/* 
	Header file for redirections.
*/
# define HEREDOC_WARNING \
"minishell: warning: here-document delimited by end-of-file (wanted `"

//Redirects.c
int		setup_redirections(t_token *token, t_minishell *shell);
int		redirect_input(const char *filename);
int		redirect_output(const char *filename, int append);

//Heredoc.c
//int		handle_heredoc(t_token *token);
//int		handle_heredoc(t_token *token, int heredoc_index);
//int handle_heredoc(t_token *token, int heredoc_index, char *heredoc_fname);
int		handle_heredoc(t_token *token, int heredoc_index, t_minishell *shell);
int		redirect_stdin_to_heredoc(const char *filename);

//Heredoc_aux.c
int		read_heredoc_lines(int fd, const char *delimiter);
//Redir_utils.c

t_token	*get_last_redirection_token(t_token *token, int type);
t_token	*get_last_relevant_path(t_token *token);
int		handle_input_redirection(t_token *token, t_minishell *shell);
int		handle_output_redirection(t_token *token);
int		handle_append_redirection(t_token *token);

//Redir_utils_2.c
char	*add_space_after_redirection(const char *arg);
int		save_original_fds(int *original_stdin, int *original_stdout);
void	restore_original_fds(int original_stdin, int original_stdout);
int		check_stat_and_errors(char *dir);
int		check_directory(char *path);

//Redir_utils_3.c
int		setup_in_redirect(t_token *token, t_minishell *shell);
int		setup_out_redirect(t_token *token, t_minishell *shell);
int		setup_append_redirect(t_token *token, t_minishell *shell);
int		setup_heredoc_redirect(t_token *token, t_minishell *shell);

//Redir_utils_4.c
void	n_f_o_d_error(char *path);
void	permission_denied_error(char *path);
void	redirect_output_error(char *path);
#endif