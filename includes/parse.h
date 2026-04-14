#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <stdio.h>
# include "minirt.h"
# include "libft.h"
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
}		t_parse;

int			check_rt_file(char *file_name);
int			check_float(char *s);
int			parse_ambient(char *res, t_objects **obj);
int			check_ambient_lightning(char *s);
int			check_color(char *s);
int			check_cords(char *s);
int			check_norm_vector(char *s);
void		print_str_arr(char **str_arr);
void		free_str_arr(char **strarr);
char		*read_rt_file(char *filename);
int			parse_light(char *s, t_objects **obj);
t_point3	parse_cords(char *s);
t_color		parse_color(char *s);
t_objects	*parse_object(char *s);

#endif