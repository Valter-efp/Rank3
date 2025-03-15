/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:37:27 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:37:28 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* 
	This heder file is to handle tokens on the parsing process.
*/

// Type definitions (CHECK THIS)
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_minishell	t_minishell;

/// @brief Struct to keep args during token split.
typedef struct s_token_args
{
	t_token	**head;// Pointer to the head of the token list
	t_token	**current;// Pointer to the current token in the list
	t_env	*env_list;// Pointer to the environment variable list
}	t_token_args;

/// @brief Struct for the env vars.
typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

/// @brief Sruct for tokens
typedef struct s_token
{
	char			*data;/* text passed on the command */
	int				type;/* what type of cammand it is */
	struct s_token	*next;/* ptr to the next token */
	struct s_token	*prev;/* ptr to the previous token */
}	t_token;

/// @brief Struct to keep args during env var expansion.
typedef struct s_env_var_args
{
	const char	*segment;
	size_t		*j;
	char		*result;
	size_t		*len;
	t_env		*env_list;
}	t_env_var_args;

/// @brief Struct to keep args during token split.
typedef struct s_segment_data
{
	const char	*input;
	char		**result;
	size_t		*count;
}	t_segment_data;

/// @brief Data struct to pass into the exit_cleaup
typedef struct s_cleanup_data
{
	t_env	*env_list;
	t_env	*export_list;
	t_token	*token_list;
	char	**args;
}	t_cleanup_data;

/// @brief Aux data struct remove input for echo command
typedef struct s_echo_params
{
	t_token		**token;
	t_minishell	*shell;
	bool		*args_removed;
	t_token		*current;
	t_token		*prev;
	bool		has_args;
}				t_echo_params;

/// @brief Data struct to pass into the execute function
typedef struct s_execution_data
{
	int			pipe_fds[2];
	int			input_fd;
	int			original_stdin;
	int			original_stdout;
	pid_t		last_pid;
	bool		is_last_command;
	bool		args_removed;
	struct stat	statbuf;
}	t_execution_data;

typedef struct s_minishell
{
	t_env		*env_list;
	t_env		*export_list;
	t_token		*token_list;
	int			exit_code;
	struct stat	*statbuf;
	int			heredoc_index;
	int			her_index_to_use;
	char		heredoc_fname[64];
}	t_minishell;

/// @brief Enum for the token type to be used in token struct
enum e_TokenType
{
	TOKEN_COMMAND			= 0,/* command to be executed, ex /bin/ls -l */
	TOKEN_IN_REDIRECT		= 1,/* `<` - redirection input */
	TOKEN_OUT_REDIRECT		= 2,/* `>` - redirection output */
	TOKEN_PIPE				= 3,/* `|` - pipes*/
	TOKEN_ARGUMENT			= 4,/* arguments or options passed to the command */
	TOKEN_DATA				= 5,/* str or filename associated with the cmd */
	TOKEN_APPEND_REDIRECT	= 6,/*  '>>' for append command */
	TOKEN_HEREDOC			= 7 /* `<<` - here-document redirection */
};

# define SYN_ERR_TKN "Syntax error: unexpected token '%s'\n"
# define SYN_ERR_END "Syntax error: unexpected end of input after '%s'\n"

//Env_utils
//t_env	*create_exit_code_node(t_ex_code *exit_code);
t_env	*initialize_env(char **envp, t_minishell *shell);
t_env	*cpy_env_to_list(char **envp);
void	free_env_list(t_env *head);
char	**env_list_to_array(t_env *env_list);

//Parse_expand_segment_aux
// char	*expand_quoted_segment(const char *token, t_env *env_list,
// 			size_t *i, char quote);
//char	*expand_unquoted_segment(const char *token, t_env *env_list, size_t *i);

//Parse_utils
char	*handle_token_with_expansions(const char *token, t_minishell *shell);
char	*join_expanded_segment(char *result, char *expanded_seg);
int		process_single_input(t_token_args *args, char *input,
			t_minishell *shell);
char	*check_empty_result(char *result, const char *token);
void	free_split_input(char **split_input);

//Parse_utils 2
char	*simplify_quotes(const char *input);
void	split_command_line_aux(const char *input, char **result,
			size_t *count);
char	**split_command_line(const char *input);

//Parse_utils 3
size_t	extract_segment(const char *input, char **result, size_t *count,
			size_t i);

//Parse
int		process_tokens(t_minishell *shell, char *line);
char	*process_token(const char *token, t_minishell *shell, size_t *i);
t_token	*make_command_tokens(const char *input, t_minishell *shell);

//Token_utils
t_token	*create_token(const char *data, int index);
int		determine_token_type(const char *data, int index);
void	add_token(t_token **head, t_token **current, char *data, int type);
void	free_tokens(t_token *head);
void	add_token_from_input(t_token_args *args, char *token,
			t_minishell *shell);

//Lexer
int		ft_lexer(t_minishell *shell);

#endif