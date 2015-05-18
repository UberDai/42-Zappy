# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/05/18 00:02:17 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	src/
OBJ_DIR		=	build/
INC_DIR		=	include libft/includes
BIN_DIR		=	bin/

NAME		=	serveur
BIN_NAME	=	$(BIN_DIR)$(NAME)
SRC_FILES	=	main.c \
				util.c \
				options.c \
				client.c \
				network.c \
				map.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC			=	clang
CC_FLAGS	=	-Wall -Werror -Wextra -g3
CC_LIBS		=	-lft -Llibft

all: libft  $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_NAME) $(CC_LIBS) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(subst $() $(), -I, $(INC_DIR)) -o $@ -c $<

clean:
	make -C libft clean
	# make -C glfw clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C libft fclean
	rm -rf $(BIN_NAME)

re: fclean all

libft:
	@make -C libft

.PHONY: all re fclean clean libft