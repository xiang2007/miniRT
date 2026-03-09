# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 22:30:05 by wshou-xi          #+#    #+#              #
#    Updated: 2026/03/09 17:45:51 by wshou-xi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I./includes
LIB = -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -Llibft -lft
RM = rm -rf

MAINDIR = src
MAINFILE = main.c math_functions.c
MAIN = $(addprefix $(MAINDIR)/,$(MAINFILE))

TDIR = src/tuple
TFILE = tuple_op.c tuple_op2.c tuple_op3.c tuple.c
T = $(addprefix $(TDIR)/,$(TFILE))

MATRIXDIR = src/matrix
MATRIXFILE = matrix.c matrix_utils.c matrix_utils2.c matrix_utils3.c
MATRIX = $(addprefix $(MATRIXDIR)/,$(MATRIXFILE))

TRANSDIR = src/transformation
TRANSFILE = translate.c scaling.c rotation.c
TRANS = $(addprefix $(TRANSDIR)/,$(TRANSFILE))

INTDIR = src/intersection
INTFILE = ray.c
INT = $(addprefix $(INTDIR)/,$(INTFILE))

SRC = $(MAIN) $(T) $(MATRIX) $(TRANS) $(INT)

OBJSDIR = obj
OBJS = $(SRC:%.c=$(OBJSDIR)/%.o)
NAME = miniRT

$(OBJSDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
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
