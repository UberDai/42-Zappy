# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/08/16 01:42:33 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR		=	src/
OBJ_DIR		=	build/
INC_DIR		=	include libft ftlst
BIN_DIR		=	bin/

NAME		=	serveur
BIN_NAME	=	$(BIN_DIR)$(NAME)
SRC_FILES	=	main.c \
				zappy.c \
				logger.c \
				util.c \
				options.c \
				network.c \
				signal.c \
				map.c \
				client/egg.c \
				client/client.c \
				client/actions.c \
				client/promote.c \
				client/broadcast.c \
				client/move.c \
				client/team.c \
				client/queue.c \
				client/item.c \
				client/vision.c \
				command/parse.c \
				command/commands.c \
				command/gfx.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC			=	clang
CC_FLAGS	=	-Wall -Werror -Wextra -pedantic -g3
CC_LIBS		=	-lft -Llibft -lftlst -Lftlst

all: ftlst libft $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_NAME) $(CC_LIBS) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS)$(subst $() $(), -I, $(INC_DIR)) -o $@ -c $<

clean:
	make -C libft clean
	make -C ftlst clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C libft fclean
	make -C ftlst fclean
	rm -rf $(BIN_NAME)

re: fclean all

libft:
	@make -C libft

ftlst:
	# git submodule init
	# git submodule update
	# git submodule foreach git pull origin master
	make -C ftlst

.PHONY: all re fclean clean libft ftlst