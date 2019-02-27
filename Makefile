# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 10:00:16 by vmuradia          #+#    #+#              #
#    Updated: 2019/02/26 16:12:17 by vmuradia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vmuradia.filler
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
SRC = main.c read.c place.c
HEADERS = filler.h
LIBFT = libft/libft.a
GREEN = \033[1;32m
OBJ=*.o

all : $(NAME)

$(NAME):
		Make -C libft
		$(CC) $(CFLAGS) $(SRC) -o $(NAME) -I $(HEADERS) -L. $(LIBFT)

		@echo "$(GREEN)Project successfully compiled"

clean :
		-rm -f $(OBJ)
		@echo "$(GREEN)All object files are deleted"

fclean : clean
		make fclean -C libft
		-rm -f $(NAME)
		@echo "$(GREEN)Cleaned everything"

re: fclean all
