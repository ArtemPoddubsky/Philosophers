# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 16:31:18 by lholdo            #+#    #+#              #
#    Updated: 2022/07/01 18:44:02 by lholdo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

FLAGS = -MMD -Wall -Werror -Wextra -pthread

DIR_S = ./

DIR_O = ./obj

SOURCES = check_args.c help_init.c init.c itoa.c main.c time_and_print.c routine.c lib_utils.c

OBJS = $(addprefix $(DIR_O)/,${SOURCES:.c=.o})

all: $(NAME)
$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $(NAME) -MMD
	@echo "\033[92mReady.\033[0m"

clean:
	@echo "\033[0;35mУдаляю объектные файлы...\033[0;31m"
	@rm -rf $(DIR_O)

fclean: clean
	@echo "\033[0;35mУдаляю исполняемый файл...\033[0;31m"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(OBJS:.o=.d)