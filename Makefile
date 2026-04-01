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
HEADERS := includes/minirt.h

MAINDIR := src
MAINFILE := main.c \
		   mlx_init.c \
		   math.c \
		   color.c \
		   camera.c \
		   minirt_init.c
MAIN := $(addprefix $(MAINDIR)/,$(MAINFILE))

VECDIR := src/vec3
VECFILE := vec3.c \
		  vec3_2.c \
		  vec3_3.c
VEC := $(addprefix $(VECDIR)/,$(VECFILE))

RAYDIR := src/ray
RAYFILE := ray.c
RAY := $(addprefix $(RAYDIR)/,$(RAYFILE))

OBJDIR := src/objects
OBJFILE := sphere.c
OBJ := $(addprefix $(OBJDIR)/,$(OBJFILE))

SRC := $(MAIN) $(VEC) $(RAY) $(OBJ)

OBJSDIR := obj
OBJS := $(SRC:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(MAKE) -C libft
	@$(MAKE) -C mlx_Linux
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJSDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)
	$(MAKE) -C mlx_Linux clean
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
