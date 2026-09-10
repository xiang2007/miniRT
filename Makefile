NAME := miniRT

# Disable Makefile printing 'Entering/Leaving directory' lines
MAKEFLAGS += --no-print-directory

CC := cc
RM := rm -rf

# ----------------------------------------------------------------------------
# Compiler flags
# -Ofast: equivalent to -O3 -ffast-math; overrides strict IEEE 754 compliance
# ----------------------------------------------------------------------------
CFLAGS := -Wall -Werror -Wextra -std=gnu11 -Ofast

# Thread-sanitizer build:  make tsan   (needs: sudo sysctl vm.mmap_rnd_bits=28)
ifdef TSAN
	CFLAGS += -fsanitize=thread -g3
	LDFLAGS += -fsanitize=thread
	# -Ofast obscures TSAN traces; downgrade to -O1
	CFLAGS := $(filter-out -Ofast,$(CFLAGS))
endif
# If TSAN fails, run this: 'sudo sysctl vm.mmap_rnd_bits=28' to run tsan

# Memory leak flags
ifdef ASAN
	CFLAGS += -ggdb -fsanitize=address -fno-omit-frame-pointer -static-libstdc++ -lrt
endif

# ----------------------------------------------------------------------------
# Preprocessor / linker
# ----------------------------------------------------------------------------
CPPFLAGS := -Iincludes -Imlx_Linux -Ilibft

LDFLAGS := -Llibft -L/usr/lib -Lmlx_Linux
# Linker library flags. Order matters.
LDLIBS := -lft -lmlx_Linux -lXext -lX11 -lm

# ----------------------------------------------------------------------------
# Headers — listed explicitly so touching one triggers a recompile
# ----------------------------------------------------------------------------
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

# ----------------------------------------------------------------------------
# Sources, grouped by module. Keep these lists in sync with src/.
# ----------------------------------------------------------------------------
MAIN := src/main.c src/rt.c

TPDIR := src/threadpool
TPSRC := threadpool.c thread_render.c threadpool_create.c
TP := $(addprefix $(TPDIR)/,$(TPSRC))

MLXDIR := src/mlx
MLXSRC := mlx_dat.c mlx_util.c mlx_event.c mlx_event2.c mlx_event3.c \
		  mlx_keymap.c mlx_loop.c mlx_controls.c
MLX := $(addprefix $(MLXDIR)/,$(MLXSRC))

PARSEDIR := src/parse
PARSESRC := parse.c \
			parse_utils.c \
			parse_cleanup.c \
			parse_file.c \
			parse_file_object.c \
			parse_file_object2.c \
			parse_check_helper.c \
			parse_check_object.c \
			parse_check_object2.c \
			parse_cone.c \
			parse_material.c \
			parse_sphere.c \
			parse_read.c
PARSE := $(addprefix $(PARSEDIR)/,$(PARSESRC))

RDRDIR := src/render
RDRSRC := render.c
RDR := $(addprefix $(RDRDIR)/,$(RDRSRC))

VECDIR := src/vec3
VECSRC := vec3_op.c vec3_util.c vec3_op2.c point_op.c vec3_rand.c vec3_rand2.c
VEC := $(addprefix $(VECDIR)/,$(VECSRC))

COLDIR := src/color
COLSRC := color.c color2.c color_util.c
COL := $(addprefix $(COLDIR)/,$(COLSRC))

RAYDIR := src/ray
RAYSRC := ray.c ray_utils.c shade.c lightning.c lightning2.c material.c shadow.c \
		  direct_lighting.c
RAY := $(addprefix $(RAYDIR)/,$(RAYSRC))

CAMDIR := src/camera
CAMSRC := camera.c
CAM := $(addprefix $(CAMDIR)/,$(CAMSRC))

OBJDIR := src/objects
OBJSRC := sphere.c plane.c cylinder.c cone.c object_utils.c object_utils2.c \
		  cylinder_hit.c cone_hit.c plane_color.c
OBJ := $(addprefix $(OBJDIR)/,$(OBJSRC))

MATDIR := src/material
MATSRC := material.c create_material.c
MAT := $(addprefix $(MATDIR)/,$(MATSRC))

OBJMVDIR := src/object_move
OBJMVSRC := obj_move.c obj_move_utils.c
OBJMV := $(addprefix $(OBJMVDIR)/,$(OBJMVSRC))

WORLDDIR := src/world
WORLDSRC := world_op.c
WORLD := $(addprefix $(WORLDDIR)/,$(WORLDSRC))

AABBDIR := src/aabb
AABBSRC := aabb.c aabb_helper.c bvh.c interval.c
AABB := $(addprefix $(AABBDIR)/,$(AABBSRC))

SRC := $(MAIN) $(MLX) $(RDR) $(VEC) $(COL) $(RAY) $(OBJ) $(CAM) $(MAT) \
	   $(OBJMV) $(WORLD) $(AABB) $(PARSE) $(TP)

# ----------------------------------------------------------------------------
# Build rules
# ----------------------------------------------------------------------------		
OBJSDIR := obj
OBJS := $(SRC:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): mlx_Linux/libmlx_Linux.a libft/libft.a $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Compile one translation unit, creating obj/ mirrors on demand.
$(OBJSDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

mlx_Linux/libmlx_Linux.a:
	@$(MAKE) -C mlx_Linux

libft/libft.a:
	@$(MAKE) -C libft

tsan: fclean
	$(MAKE) TSAN=1 re

asan: fclean
	$(MAKE) ASAN=1 re

clean:
	$(RM) $(OBJSDIR)
	$(MAKE) -C mlx_Linux clean
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re tsan
