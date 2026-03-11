#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx_Linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# define EP 1e-9
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846
# define ASPECT_RATIO 16 / 9

typedef struct	s_mlx
{
	void	*img;
	void	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}				t_color;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3	point;
	t_vec3	vec;
}				t_ray;

void	init_mlx(t_mlx *m);
void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);
int		close_all(t_mlx *data);

double	sq(double r);


t_vec3	add_vec(t_vec3 a, t_vec3 b);
t_vec3	sub_vec(t_vec3 a, t_vec3 b);
t_vec3	neg_vec(t_vec3 a);
t_vec3	scale_vec(t_vec3 a, double t);
t_vec3	div_vec(t_vec3 a, double t);
double	len_sq(t_vec3 a);
double	len_vec(t_vec3 a);
t_vec3	cross_vec(t_vec3 a, t_vec3 b);
double	dot_vec(t_vec3 a, t_vec3 b);
t_vec3	unit_vec(t_vec3 a);

double	ray_pos(t_ray r, double t);

#endif