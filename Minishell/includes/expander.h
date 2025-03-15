/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:13 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:14 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

//Expander_utils
char	*extract_var_name(const char *token);
char	*get_variable_value(t_minishell *shell, const char *var_name);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*expand_quoted_segment(const char *token, t_minishell *shell, size_t *i,
			char quote);

//Expander
char	*expand_segment(const char *token, t_minishell *shell, size_t *i,
			char quote);
char	*expand_variable(t_minishell *shell, const char *token);
char	*expand_and_join(char *result, char *segment, t_minishell *shell,
			char quote);
char	*process_expansion_segment(const char *token, size_t *i, char quote);

//Quotes_utils
int		check_unclosed_quotes(const char *token);
char	*do_dq(t_minishell *shell, const char *token);
char	*expand_exit_code(t_minishell *shell);

//Expander_unquoted_segment
char	*expand_exit_code(t_minishell *shell);
char	*handle_dollar(char *segment, t_minishell *shell,
			char *expanded_seg, size_t *j);
char	*append_char_to_segment(char *segment, char *expanded_seg, size_t *j);
char	*expand_unquoted_segment(const char *token, t_minishell *shell,
			size_t *i);

//Expander_unquoted_segment_aux
void	process_char(const char **src, char **dest, int *dollar_count);
char	*preprocess_segment(const char *segment);
#endif