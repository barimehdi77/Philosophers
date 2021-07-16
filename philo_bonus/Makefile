# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbari <mbari@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 12:34:25 by mbari             #+#    #+#              #
#    Updated: 2021/07/16 09:07:41 by mbari            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable files
NAME = ./philo_bonus


# Project's directories
OBJECTSDIR = objects
HEADERFILE = philosophers.h


# Name of variables
FLAGS = -Wall -Wextra -Werror
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


# philosophers files variable
SRC_FILES = ft_parsing.c \
philosophers.c \
ft_actions.c \
ft_init.c \



# Define objects for all sources
OBJS := $(addprefix $(OBJECTSDIR)/, $(SRC_FILES:.c=.o))

# Name the compiler
CC = gcc

# OS specific part
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null

all: credit $(NAME)
	@echo "$(BLUE)██████████████████████ Compiling is DONE ███████████████████████$(RESET)"
	@echo "         Made with love by : \033[1;91mmbari\033[m"

head:
	@echo "$(BLUE)██████████████████████ Making Philosophers █████████████████████$(RESET)"

# philosophers making rules
$(NAME): head $(OBJS)
	@$(CC) -I $(HEADERFILE) $(OBJS) -o $@

$(OBJECTSDIR)/%.o: %.c $(HEADERFILE)
	@$(MKDIR) $(dir $@)
	@echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	@$(CC) $(FLAGS) -I $(HEADERFILE) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build
clean:
	@echo "$(RED)deleting$(RESET): " $(OBJECTSDIR)
	@$(RMDIR) $(OBJECTSDIR)


fclean: clean
	@echo "$(RED)deleting$(RESET): " $(NAME)
	@$(RM) $(NAME) philo_bonus.dSYM $(ERRIGNORE)

re: fclean all

# Print Credit
credit:
	@echo "▀██▀▀█▄  ▀██       ██  ▀██                                  ▀██"
	@echo " ██   ██  ██ ▄▄   ▄▄▄   ██    ▄▄▄    ▄▄▄▄    ▄▄▄   ▄▄▄ ▄▄▄   ██ ▄▄     ▄▄▄▄  ▄▄▄ ▄▄   ▄▄▄▄"
	@echo " ██▄▄▄█▀  ██▀ ██   ██   ██  ▄█  ▀█▄ ██▄ ▀  ▄█  ▀█▄  ██▀  ██  ██▀ ██  ▄█▄▄▄██  ██▀ ▀▀ ██▄ ▀"
	@echo " ██       ██  ██   ██   ██  ██   ██ ▄ ▀█▄▄ ██   ██  ██    █  ██  ██  ██       ██     ▄ ▀█▄▄"
	@echo "▄██▄     ▄██▄ ██▄ ▄██▄ ▄██▄  ▀█▄▄█▀ █▀▄▄█▀  ▀█▄▄█▀  ██▄▄▄▀  ▄██▄ ██▄  ▀█▄▄▄▀ ▄██▄    █▀▄▄█▀"
	@echo "                                                    ██"
	@echo "         Made with love by : \033[1;91mmbari\033[m                 ▀▀▀▀"
