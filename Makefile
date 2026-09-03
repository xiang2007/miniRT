NAME := miniRT

# Disable Makefile printing 'Entering/Leaving directory' lines
MAKEFLAGS += --no-print-directory
MAKE := make

CC := cc
RM := rm -rf

# Memory leak flags
ifdef ML
	CFLAGS += -ggdb -fsanitize=address -fno-omit-frame-pointer -static-libstdc++ -lrt
endif

# Compiler Flags
# -Ofast: equivalent to -O3 -ffast-math, enables compiler optimizations and overrides standard math compliance to IEE 754
CFLAGS := -Wall -Werror -Wextra -std=gnu11 -g3 -Ofast $(ML)

# If TSAN=1 is passed, append the sanitize flags
ifdef TSAN
	CFLAGS += -fsanitize=thread -g3 -O1
	LDFLAGS += -fsanitize=thread
	# Overwrite -Ofast to -O1 because heavy optimization messes with TSAN traces
	CFLAGS := $(filter-out -Ofast,$(CFLAGS))
endif

# Need to enable this: sudo sysctl vm.mmap_rnd_bits=28 to run tsan
# 

# Preprocessor flags
CPPFLAGS := -Iincludes -Imlx_linux -Ilibft

# Debug mode
#CPPFLAGS += -DDEBUG=1

# Linker search path flags
LDFLAGS := -Llibft -L/usr/lib -Lmlx_Linux

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
		   includes/objects.h \
		   includes/material.h \
		   includes/threadpool.h \
		   includes/parse.h \
		   includes/aabb.h

MAIN := src/main.c src/rt.c

TPDIR := src/threadpool
TPSRC := threadpool.c \
		  thread_render.c
TP := $(addprefix $(TPDIR)/,$(TPSRC))

MLXDIR := src/mlx
MLXSRC := mlx_dat.c \
		  mlx_util.c \
		  mlx_event.c \
		  mlx_event2.c \
		  mlx_event3.c
MLX := $(addprefix $(MLXDIR)/,$(MLXSRC))

PARSEDIR := src/parse
PARSESRC := parse_check_helper.c parse_check_object.c parse_check_object2.c \
			parse_cleanup.c parse_file_object.c parse_file.c parse_utils.c \
			parse.c parse_file_object2.c parse_cone.c
PARSE := $(addprefix $(PARSEDIR)/,$(PARSESRC))

RDRDIR := src/render
RDRSRC := render.c
RDR := $(addprefix $(RDRDIR)/,$(RDRSRC))

VECDIR := src/vec3
VECSRC := vec3_op.c \
		  vec3_util.c \
		  point_op.c \
		  vec3_rand.c \
		  vec3_rand2.c \
		  vec3_op2.c
VEC := $(addprefix $(VECDIR)/,$(VECSRC))

COLDIR := src/color
COLSRC := color.c \
		  color2.c \
		  color_util.c
COL := $(addprefix $(COLDIR)/,$(COLSRC))

RAYDIR := src/ray
RAYSRC := lightning.c \
		  lightning2.c \
		  ray.c \
		  ray_utils.c \
		  material.c \
		  shade.c
RAY := $(addprefix $(RAYDIR)/,$(RAYSRC))

CAMDIR := src/camera
CAMSRC := camera.c
CAM := $(addprefix $(CAMDIR)/,$(CAMSRC))

OBJDIR := src/objects
OBJSRC := sphere.c \
		  object_utils.c \
		  object_utils2.c
OBJ := $(addprefix $(OBJDIR)/,$(OBJSRC))

MATDIR := src/material
MATSRC := material.c \
		  create_material.c
MAT := $(addprefix $(MATDIR)/,$(MATSRC))

OBJMVDIR := src/object_move
OBJMVSRC := obj_move.c obj_move_utils.c
OBJMV := $(addprefix $(OBJMVDIR)/,$(OBJMVSRC))

INTDIR := src/intersection
INTSRC := intersection_hit.c \
		  intersection_hit2.c
INT := $(addprefix $(INTDIR)/,$(INTSRC))

WORLDDIR := src/world
WORLDSRC := world_op.c
WORLD := $(addprefix $(WORLDDIR)/,$(WORLDSRC))

AABBDIR := src/aabb
AABBSRC := aabb.c bvh.c interval.c aabb_helper.c
AABB := $(addprefix $(AABBDIR)/,$(AABBSRC))

SRC := $(MAIN) $(MLX) $(RDR) $(VEC) $(COL) $(RAY) $(OBJ) $(CAM) $(INT) $(PARSE) $(WORLD) $(OBJMV) $(MAT) $(AABB) $(TP)

OBJSDIR := obj
OBJS := $(SRC:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): mlx_Linux/libmlx_Linux.a libft/libft.a $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

tsan: fclean
	$(MAKE) TSAN=1 re
	
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

.PHONY: all clean fclean re tsan
