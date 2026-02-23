# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 22:30:05 by wshou-xi          #+#    #+#              #
#    Updated: 2026/02/23 11:07:41 by wshou-xi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I./includes
LIB = -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -Llibft -lft
RM = rm -rf

MAINDIR = src
MAINFILE = main.c
MAIN = $(addprefix $(MAINDIR)/,$(MAINFILE))

MATHDIR = src/math
MATHFILE = tuple_math.c tuple_math2.c tuple.c tuple_math3.c
MATH = $(addprefix $(MATHDIR)/,$(MATHFILE))

MLXDIR = src/mlx
MLXFILE = mlx_init.c
MLX = $(addprefix $(MLXDIR)/,$(MLXFILE))

RAYDIR = src/ray
RAYFILE = ray.c intersect.c transform_ray.c transform_sphere.c
RAY = $(addprefix $(RAYDIR)/,$(RAYFILE))

MATRIXDIR= src/matrix
MATRIXFILE = matrix.c matrix_utils.c matrix_utils2.c sub_matrix.c cofactor.c \
				inverse.c translation.c multiplication.c scaling.c rotation.c \
				rotation2.c
MTX = $(addprefix $(MATRIXDIR)/,$(MATRIXFILE))

OBJDIR = src/objects
OBJFILE = ambient_lightning.c camera.c cylinder.c objects.c plane.c sphere.c
OBJ = $(addprefix $(OBJDIR)/,$(OBJFILE))

SRC = $(MAIN) $(MATH) $(MLX) $(MTX) $(RAY) $(OBJ)

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
