# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 15:57:02 by vafernan          #+#    #+#              #
#    Updated: 2025/02/04 14:26:13 by vafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philo

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
# Source selection
SRC_DIR = sources
OBJ_DIR = obj
SRC =	$(SRC_DIR)/dinner.c \
		$(SRC_DIR)/handle_error_and_exit.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/philo.c \
		$(SRC_DIR)/forks.c \
		$(SRC_DIR)/init_philo_forks_threads.c \
		$(SRC_DIR)/philo_action.c \
		$(SRC_DIR)/utils.c
OBJ =	$(OBJ_DIR)/dinner.o \
		$(OBJ_DIR)/handle_error_and_exit.o \
		$(OBJ_DIR)/parser.o \
		$(OBJ_DIR)/philo.o \
		$(OBJ_DIR)/forks.o \
		$(OBJ_DIR)/init_philo_forks_threads.o \
		$(OBJ_DIR)/philo_action.o \
		$(OBJ_DIR)/utils.o

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/dinner.o: $(SRC_DIR)/dinner.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/handle_error_and_exit.o: $(SRC_DIR)/handle_error_and_exit.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/philo.o: $(SRC_DIR)/philo.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/forks.o: $(SRC_DIR)/forks.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/init_philo_forks_threads.o: $(SRC_DIR)/init_philo_forks_threads.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/philo_action.o: $(SRC_DIR)/philo_action.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

#Rule to check race conditions
sanitizeThreads: CFLAGS += -fsanitize=thread
sanitizeThreads: re

#Rule to check memory leaks
sanitizeAddress: CFLAGS += -fsanitize=address
sanitizeAddress: re

.PHONY: all clean fclean re
#Valgrind tests
#valgrind --tool=drd -s ./philo 3 310 200 100
#valgrind --tool=helgrind ./philo 3 310 200 100