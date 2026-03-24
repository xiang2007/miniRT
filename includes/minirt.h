/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:57:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 15:21:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx_Linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# define EP 1e-9
# define WIDTH 800
# define PI 3.14159265358979323846
# define ASPECT_RATIO 1.7777777777777777777777777777778

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}			t_obj_type;

typedef struct s_vec3
{
	union
	{
		struct
		{
			double	x;
			double	y;
			double	z;
		};
		struct
		{
			double	r;
			double	g;
			double	b;
			double	color;
		};
	};
} t_vec3, t_color,	t_point3;

/// @brief point is used as the center of the sphere
typedef struct s_sphere
{
	t_point3	point;
	double		radius;
	int			color;
}				t_sphere;

typedef struct s_plane
{
	t_point3	center;
	t_vec3		normal;
	int			color;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	int			color;
}				t_cylinder;

typedef struct s_objects
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_objects;

typedef struct s_interval
{
	double	min;
	double	max;
}				t_interval;

typedef struct s_mlx
{
	void	*img;
	void	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_mrt
{
	double	image_height;
	double	image_width;
	double	viewport_height;
	double	viewport_width;
	t_vec3	cam_center;
	t_mlx	*mlx;
}				t_mrt;

typedef struct s_cam
{
	int		image_width;
	int		image_height;
	double	fov;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	t_vec3	cam_center;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_vec3	viewport_upper_left;
	t_vec3	pixel00_loc;
}				t_cam;

typedef struct s_ray
{
	t_point3	point;
	t_vec3		vec;
}				t_ray;

typedef struct s_ray_min_max
{
	double	r_min;
	double	r_max;
}				t_ray_min_max;

t_mlx	*init_mlx(int image_height);
void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);
void	mlx_free_all(t_mlx *data);
int		close_all(t_mlx *data);

double	sq(double r);
t_mrt	*init_mrt(void);
void	free_mrt(t_mrt *m);

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
t_vec3	create_vec3(double a, double b, double c);
t_vec3	mult_vec3(t_vec3 a, t_vec3 b);
void	print_vec3(t_vec3 v);

t_color	add_color(t_color a, t_color b);
t_color	mult_color(t_color a, t_color b);
t_color	mult_color_n(t_color c, double n);
t_color	create_color(double r, double g, double b);
int		rgb_to_hex(int r, int g, int b);

t_cam	cam(t_mrt mrt);
void	print_cam(t_cam	c);
void	render(t_mrt *m, t_cam c);

t_vec3	ray_pos(t_ray r, double t);
t_ray	ray(t_point3 cam_center, t_vec3 ray_dir);
t_color	ray_color(t_ray r, t_sphere sp);
double	hit_sphere(t_vec3 center, double radius, t_ray r);

#endif