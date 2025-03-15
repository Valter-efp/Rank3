/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:10 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:11 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"

# define N_F_O_DR " No such file or directory\n"
# define SYN_ERR "minishell: syntax error near unexpected token `newline'\n"
# define N_V_ID " not a valid identifier\n"
//execute_utils
int		count_args(t_token *list);
char	**initialize_args(int size);
void	fill_args(char **args, t_token *list);
void	copy_double_pointer(char ***ambiente, char **envp);
void	cleanup_args(char **args);

//execute_utils2
int		run_commands_with_args(t_token *current_command, t_minishell *shell);
t_token	*get_next_pipe(t_token *token);
t_token	*get_next_command(t_token *token);
void	handle_builtin_cmds(t_token *current_command, t_minishell *shell,
			t_token *list);
void	wait_for_children(t_minishell *shell, pid_t last_pid);

//execute_utils_echo
int		is_echo_command(t_token *token);
bool	rmv_inputredir_echo(t_token **token, t_minishell *shell,
			bool *args_removed);

//native_cmds_utils
int		run_native_cmds(char **args, t_minishell *shell);
char	**get_all_dirs(char *path_env);
void	wait_for_child_process(pid_t pid);

//native_cmds_utils2
int		execute_command_in_path(char **args, char **envp, char **path_dirs);
char	*make_full_path(const char *dir, const char *command);
int		do_command(const char *full_path, char **args, char **envp);

//native_cmds_utils3
int		r_handle_child_process(char **args, t_minishell *shell);

//execute
int		is_echo_command(t_token *token);
void	execute(t_token *list, t_minishell *shell);

//execute_aux
int		handle_child(t_execution_data *data, t_token *current_command,
			t_minishell *shell);
int		handle_parent(t_execution_data *data, pid_t pid);
int		fork_and_redirect(t_execution_data *data, t_token *current_command,
			t_minishell *shell);
int		handle_builtin(t_execution_data *data, t_token *current_command,
			t_minishell *shell, t_token *list);
int		handle_pipe_and_fork(t_execution_data *data, t_token *current_command,
			t_minishell *shell);

//execute_aux_hd
int		ft_heredocmanage(t_token *list, t_minishell *shell);

//run_commands
int		is_builtin_command(char *cmd);
void	execute_command(char *cmd, char **args, char **path_dirs);
void	execute_native_command(char **args);
void	run_builtin_cmds(char **args, t_minishell *shell, t_token *token_list);
void	run_commands(char **args, t_minishell *shell, t_token *token_list);

//builtins
//cd
int		ft_cd(char **args);

//echo
int		ft_echo(char **args, int last_exit_code);
void	print_arg(char *arg, int last_exit_code);

//env
int		ft_env(t_env *env_list);

//exit
void	init_cleanup_lists(t_cleanup_data *data, t_env *env_list,
			t_env *export_list, t_token *token_list);
void	init_cleanup_args(t_cleanup_data *data, char **args);
int		exit_cleanup(int exit_code, t_cleanup_data *data);
int		ft_exit(char **args, t_env *env_list, t_env *export_list,
			t_token *token_list);

//export_utils
void	add_to_sorted_list(t_env **list, t_env *new_node);
int		just_key(t_minishell *shell, char **args);
char	*clean_value(char *value);

//export_utils2
int		key_value(t_minishell *shell, char **args, char *equal_sign);

//export_utils3
int		is_valid_identifier(const char *str);
void	handle_invalid_identifier(char *identifier, t_minishell *shell,
			char *equal_sign);
void	handle_valid_identifier(char *arg, char *equal_sign,
			t_minishell *shell);
int		replace_value(t_env *current, t_env *new_node);
//export
int		ft_ex_print(t_env *temp);
void	process_export_argument(char *arg, t_minishell *shell);
int		ft_export(char **args, t_minishell *shell);
//pwd
int		ft_pwd(void);
//unset
void	remove_node(t_env **list, const char *var);
int		ft_unset(char **args, t_env **export_list, t_env **env_list);

#endif