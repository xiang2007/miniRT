#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <stdio.h>
# include "minirt.h"
# include "../libft/libft.h"
# include "objects.h"
# define TRUE 1
# define FALSE 0
# define BUF_SIZE 100

typedef struct s_parse
{
	int	ambient;
	int	camera;
	int	cylinder;
	int	light;
	int	sphere;
	int	plane;
	int	object;
}		t_parse;

// Object checking function
int	check_sphere(char *s);
int	check_plane(char *s);
int	check_light(char *s);
int	check_cam(char *s);
int	check_ambient_lightning(char *s);
int	check_cylinder(char *s);

// Object checking function helper
int	check_float(char *s);
int	check_color(char *s);
int	check_cords(char *s);
int	check_norm_vector(char *s);

// Parsing functions
int	parse_light(int id, char *s, t_objects **obj);
int	parse_cam(int id, char *s, t_objects **obj);
int	parse_ambient(int id, char *res, t_objects **obj);
int	parse_sphere(int id, char *s, t_objects **obj);
int	parse_plane(int id, char *s, t_objects **obj);
int	parse_cylinder(int id, char *s, t_objects **obj);

// Parsing helper functions
int		check_rt_file(char *file_name);
int		parse_arg_count(char **arg);
char	*read_rt_file(char *filename);
void	print_str_arr(char **str_arr);
void	free_str_arr(char **strarr);
void	print_objects(t_objects *o);
t_point3	parse_cords(char *s);
t_color		parse_color(char *s);
t_objects	*parse_object(char **res);

// Parsing cleaning function
void	parse_free_objects(t_objects *o);

// Main parsing function
t_objects	*parse(char *file);

#endif
