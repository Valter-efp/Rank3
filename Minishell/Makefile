# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 15:45:54 by vafernan          #+#    #+#              #
#    Updated: 2025/02/03 17:01:50 by vafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I../libft -I../libft/GNL #-fsanitize=address

# Readline library path and flags
RLFLAG = -lreadline -lhistory

# Directories
SRC_DIR = sources
PARSER_DIR = $(SRC_DIR)/parser
EXECUTE_DIR = $(SRC_DIR)/execute
EX_UTILS_DIR = $(EXECUTE_DIR)/utils
BUILTINS_DIR = $(EXECUTE_DIR)/builtins
EXPANDER_DIR = $(SRC_DIR)/expander
REDIRECTS_DIR = $(SRC_DIR)/redirects
OBJ_DIR = objects
LIBFT_DIR = libft

# Source and object files
SRC = 	$(BUILTINS_DIR)/cd.c \
		$(BUILTINS_DIR)/echo.c \
		$(BUILTINS_DIR)/env.c \
		$(BUILTINS_DIR)/exit.c \
		$(BUILTINS_DIR)/export_utils.c \
		$(BUILTINS_DIR)/export_utils2.c \
		$(BUILTINS_DIR)/export_utils3.c \
		$(BUILTINS_DIR)/export.c \
		$(BUILTINS_DIR)/pwd.c \
		$(BUILTINS_DIR)/unset.c \
		$(EX_UTILS_DIR)/execute_utils_echo.c \
		$(EX_UTILS_DIR)/execute_utils.c \
		$(EX_UTILS_DIR)/execute_utils2.c \
		$(EX_UTILS_DIR)/native_cmds_utils.c \
		$(EX_UTILS_DIR)/native_cmds_utils2.c \
		$(EX_UTILS_DIR)/native_cmds_utils3.c \
		$(EXECUTE_DIR)/execute_aux.c \
		$(EXECUTE_DIR)/execute_aux_hd.c \
		$(EXECUTE_DIR)/execute.c \
		$(EXECUTE_DIR)/run_commands.c \
		$(EXPANDER_DIR)/expander_unquoted_segment.c \
		$(EXPANDER_DIR)/expander_unquoted_segment_aux.c \
		$(EXPANDER_DIR)/expander_utils.c \
		$(EXPANDER_DIR)/expander.c \
		$(EXPANDER_DIR)/quote_utils.c \
		$(PARSER_DIR)/env_utils.c \
		$(PARSER_DIR)/lexer.c \
		$(PARSER_DIR)/parse_utils.c \
		$(PARSER_DIR)/parse_utils2.c \
		$(PARSER_DIR)/parse_utils3.c \
		$(PARSER_DIR)/parse.c \
		$(PARSER_DIR)/token_utils.c \
		$(REDIRECTS_DIR)/heredoc.c \
		$(REDIRECTS_DIR)/heredoc_aux.c \
		$(REDIRECTS_DIR)/redir_utils.c \
		$(REDIRECTS_DIR)/redir_utils2.c \
		$(REDIRECTS_DIR)/redir_utils3.c \
		$(REDIRECTS_DIR)/redir_utils4.c \
		$(REDIRECTS_DIR)/redirects.c \
		$(SRC_DIR)/main_utils.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/signals.c
	
OBJ = $(OBJ_DIR)/execute/builtins/cd.o \
	  $(OBJ_DIR)/execute/builtins/echo.o \
	  $(OBJ_DIR)/execute/builtins/env.o \
	  $(OBJ_DIR)/execute/builtins/exit.o \
	  $(OBJ_DIR)/execute/builtins/export_utils.o \
	  $(OBJ_DIR)/execute/builtins/export_utils2.o \
	  $(OBJ_DIR)/execute/builtins/export_utils3.o \
	  $(OBJ_DIR)/execute/builtins/export.o \
	  $(OBJ_DIR)/execute/builtins/pwd.o \
	  $(OBJ_DIR)/execute/builtins/unset.o \
	  $(OBJ_DIR)/execute/utils/execute_utils_echo.o \
	  $(OBJ_DIR)/execute/utils/execute_utils.o \
	  $(OBJ_DIR)/execute/utils/execute_utils2.o \
	  $(OBJ_DIR)/execute/utils/native_cmds_utils.o \
	  $(OBJ_DIR)/execute/utils/native_cmds_utils2.o \
	  $(OBJ_DIR)/execute/utils/native_cmds_utils3.o \
	  $(OBJ_DIR)/execute/execute_aux.o \
	  $(OBJ_DIR)/execute/execute_aux_hd.o \
	  $(OBJ_DIR)/execute/execute.o \
	  $(OBJ_DIR)/execute/run_commands.o \
	  $(OBJ_DIR)/expander/expander_unquoted_segment.o \
	  $(OBJ_DIR)/expander/expander_unquoted_segment_aux.o \
	  $(OBJ_DIR)/expander/expander_utils.o \
	  $(OBJ_DIR)/expander/expander.o \
	  $(OBJ_DIR)/expander/quotes_utils.o \
	  $(OBJ_DIR)/parser/env_utils.o \
	  $(OBJ_DIR)/parser/lexer.o \
	  $(OBJ_DIR)/parser/parse_utils.o \
	  $(OBJ_DIR)/parser/parse_utils2.o \
	  $(OBJ_DIR)/parser/parse_utils3.o \
	  $(OBJ_DIR)/parser/parse.o \
	  $(OBJ_DIR)/parser/token_utils.o \
	  $(OBJ_DIR)/redirects/heredoc.o \
	  $(OBJ_DIR)/redirects/heredoc_aux.o \
	  $(OBJ_DIR)/redirects/redir_utils.o \
	  $(OBJ_DIR)/redirects/redir_utils2.o \
	  $(OBJ_DIR)/redirects/redir_utils3.o \
	  $(OBJ_DIR)/redirects/redir_utils4.o \
	  $(OBJ_DIR)/redirects/redirects.o \
	  $(OBJ_DIR)/main_utils.o \
	  $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/signals.o

# Library flags
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# ANSI color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
RESET = \033[0m

# Rules
all: welcome_message $(OBJ_DIR) $(NAME)

welcome_message:
	@echo "$(BLUE)---------------------------------------------$(RESET)"
	@echo "$(CYAN)Welcome to ralves-e && vafernan minishell!$(RESET)"
	@echo "$(YELLOW)Main rule:$(RESET)"
	@echo "$(RED)if (minishell(output) != bash(output))"
	@echo "     minishell(output) = bash(output);$(RESET)"
	@echo "$(BLUE)---------------------------------------------$(RESET)"

$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(RLFLAG) -o $(NAME) > /dev/null
	@echo "$(GREEN)Minishell recompiled successfully!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parser $(OBJ_DIR)/execute $(OBJ_DIR)/execute/builtins $(OBJ_DIR)/execute/utils $(OBJ_DIR)/expander $(OBJ_DIR)/redirects > /dev/null

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/parser/%.o: $(PARSER_DIR)/%.c | $(OBJ_DIR)/parser
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/execute/%.o: $(EXECUTE_DIR)/%.c | $(OBJ_DIR)/execute
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/execute/builtins/%.o: $(BUILTINS_DIR)/%.c | $(OBJ_DIR)/execute/builtins
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/execute/utils/%.o: $(EX_UTILS_DIR)/%.c | $(OBJ_DIR)/execute/utils
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/expander/%.o: $(EXPANDER_DIR)/%.c | $(OBJ_DIR)/expander
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

$(OBJ_DIR)/redirects/%.o: $(REDIRECTS_DIR)/%.c | $(OBJ_DIR)/redirects
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

valgrind:
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@rm -f $(TERMSYNC_OBJ)

re: fclean all

# Tester rule
tester:
	@git clone git@github.com:LucasKuhn/minishell_tester.git

# Remove tester folder rule
rmtester:
	@rm -rf minishell_tester

.PHONY: all clean fclean re termsync
