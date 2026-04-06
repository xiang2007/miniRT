NAME := miniRT

# Disable Makefile printing 'Entering/Leaving directory' lines
MAKEFLAGS += --no-print-directory
MAKE := make

CC := cc
RM := rm -rf

# Compiler Flags
CFLAGS := -Wall -Werror -Wextra -g3

# Preprocessor flags
CPPFLAGS := -Iincludes -Imlx_linux -Ilibft

# Debug mode
#CPPFLAGS += -DDEBUG=1

# Linker search path flags
LDFLAGS := -Llibft -L/usr/lib -Lmlx_linux

# Linker library flags. Order matters.
LDLIBS := -lft -lmlx_Linux -lXext -lX11 -lm

# List out headers as dependencies and ensures the compiler will recompile if the header files are modified
HEADERS := includes/minirt.h \
		   includes/mlx_dat.h \
		   includes/vec3.h \
		   includes/color.h \
		   includes/camera.h \
		   includes/ray.h \
		   includes/render.h \
		   includes/objects.h

MAIN := src/main.c

MLXDIR := src/mlx
MLXSRC := mlx_dat.c \
		  mlx_util.c
MLX := $(addprefix $(MLXDIR)/,$(MLXSRC))

RDRDIR := src/render
RDRSRC := render.c
RDR := $(addprefix $(RDRDIR)/,$(RDRSRC))

VECDIR := src/vec3
VECSRC := vec3_op.c \
		  vec3_util.c
VEC := $(addprefix $(VECDIR)/,$(VECSRC))

COLDIR := src/color
COLSRC := color.c \
		  color_util.c
COL := $(addprefix $(COLDIR)/,$(COLSRC))

RAYDIR := src/ray
RAYSRC := ray.c
RAY := $(addprefix $(RAYDIR)/,$(RAYSRC))

CAMDIR := src/camera
CAMSRC := camera.c
CAM := $(addprefix $(CAMDIR)/,$(CAMSRC))

OBJDIR := src/objects
OBJSRC := sphere.c
OBJ := $(addprefix $(OBJDIR)/,$(OBJSRC))

INTDIR := src/intersection
INTSRC := intersection_hit.c
INT := $(addprefix $(INTDIR)/,$(INTSRC))

SRC := $(MAIN) $(MLX) $(RDR) $(VEC) $(COL) $(RAY) $(CAM) $(OBJ) $(INT)

OBJSDIR := obj
OBJS := $(SRC:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): mlx_Linux/libmlx_Linux.a libft/libft.a $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJSDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

mlx_Linux/libmlx_Linux.a:
	@$(MAKE) -C mlx_Linux

libft/libft.a:
	@$(MAKE) -C libft

clean:
	$(RM) $(OBJSDIR)
	$(MAKE) -C mlx_Linux clean
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
