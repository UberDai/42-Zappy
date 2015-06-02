#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 13:13:41 by amaurer           #+#    #+#              #
#    Updated: 2015/02/10 08:41:38 by amaurer          ###   ########.fr        #
#                                                                              #
#******************************************************************************#
CC = cc
NAME = libft.a
PATH_OBJ = obj
PATH_SRC = src
PATH_INC = ./
CFLAGS = -Wall -Werror -Wextra -g3 -I$(PATH_INC)
SRC = $(shell ls -1 $(PATH_SRC) | grep .c)
OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : $(NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(NAME) : $(OBJ)
	@ar rc $@ $^
	@ranlib $@

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -c $^

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re $(NAME)
