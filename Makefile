# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 22:30:05 by wshou-xi          #+#    #+#              #
#    Updated: 2026/02/12 22:30:05 by wshou-xi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I./includes
LIB = -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm
RM = rm -rf

SRC = 
OBJS = $(SRC:.c=.o)
NAME = miniRT

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):
	@$(MAKE) -C libft
	@$(MAKE) -C mlx_Linux
	@$(CC) $(CFLAGS) $(SRC) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)
	$(MAKE) -C mlx_Linux clean
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
