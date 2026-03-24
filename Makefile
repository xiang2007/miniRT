# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 22:30:05 by wshou-xi          #+#    #+#              #
#    Updated: 2026/03/24 15:03:51 by wshou-xi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I./includes
LIB = -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -Llibft -lft
RM = rm -rf

MAINDIR = src
MAINFILE = main.c mlx_init.c math.c color.c camera.c minirt_init.c
MAIN = $(addprefix $(MAINDIR)/,$(MAINFILE))

VECDIR = src/vec3
VECFILE = vec3.c vec3_2.c vec3_3.c
VEC = $(addprefix $(VECDIR)/,$(VECFILE))

RAYDIR = src/ray
RAYFILE = ray.c
RAY = $(addprefix $(RAYDIR)/,$(RAYFILE))

OBJDIR = src/objs
OBJFILE = objs.c
OBJ = $(addprefix $(OBJSDIR)/,$(OBJSFILE))

SRC = $(MAIN) $(VEC) $(RAY)

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
