/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:05:41 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 14:09:10 by wshou-xi         ###   ########.fr       */
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
# define EP 1e-9
# define WIDTH 800
# define HEIGHT 800
# define PI 3.14159265358979323846
# define POINT 1
# define VECTOR 0

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
	int		free;
}				t_tuple;

typedef struct	s_matrix
{
	double	**matrix;
	int		row;
	int		col;
}				t_matrix;

typedef struct	s_ray
{
	t_tuple	*point;
	t_tuple	*direction;
}				t_ray;

typedef struct	s_dis
{
	t_tuple	*sphere_to_ray;
	double	a;
	double	b;
	double	c;
	double	res;
}				t_dis;

typedef struct	s_sphere
{
	int			id;
	double		size;
	t_matrix	*transform_matrix;
	t_tuple	*point;
}				t_sphere;

typedef enum	e_object_type
{
	SPHERE
}				t_object_type;

typedef struct	s_object
{
	t_object_type	type;
	t_sphere		*sp;
}				t_object;

typedef struct	s_intersect
{
	int					intersect_count;
	double				*intersects;
	t_object_type		type;
	void				*object;
	struct s_intersect	*next;
}				t_intersect;

t_tuple	*create_tuple(double x, double y, double z, double w);
t_tuple	*create_point(double x, double y, double z);
t_tuple	*create_vector(double x, double y, double z);
t_tuple	*create_temp_tuple(double x, double y, double z, double w);

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*negate_tuple(t_tuple *t1);
void	print_tuple(t_tuple *t);
t_tuple	*tuple_dup(t_tuple *t);
void	free_temp_tuple(t_tuple *t);
double	magnitde(t_tuple *t);
t_tuple	*tuple_normalize(t_tuple *t);
double	dot_product(t_tuple *t1, t_tuple *t2);
t_tuple	*mult_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_cross(t_tuple *t1, t_tuple *t2);

t_matrix	*create_matrix(int row, int col);
void		print_mat(t_matrix *m);
void		free_matrix(t_matrix *m);
void		set_mat_value(t_matrix *m, int val, int row, int col);
int			compare_matrix(t_matrix *m1, t_matrix *m2);
t_matrix	*multiply_matrix(t_matrix *m1, t_matrix *m2);
t_tuple		*mult_tuple_matrix(t_tuple *t, t_matrix *mt);
t_matrix	*create_identity_matrix();
t_matrix	*transpose_matrix(t_matrix *m);
t_matrix	*submatrix(t_matrix *m, int row, int col);
double		matrix_cofactor(t_matrix *mt, int row, int col);
double		matrix_determinant(t_matrix *m);
double		matrix_minor(t_matrix *m, int row, int col);
t_matrix	*matrix_inverse(t_matrix *m);

t_tuple	*matrix_translation(t_tuple *p, double x, double y, double z);
t_tuple	*matrix_translation_inv(t_tuple *p, double x, double y, double z);
t_tuple	*matrix_scaling(t_tuple *p, double x, double y, double z);
t_tuple	*matrix_scaling_inv(t_tuple *p, double x, double y, double z);
t_tuple	*matrix_reflection(t_tuple *t);
t_tuple	*matrix_rotation_x(t_tuple *p, double deg);
t_tuple	*matrix_rotation_y(t_tuple *p, double deg);
t_tuple	*matrix_rotation_z(t_tuple *p, double deg);

t_sphere	*create_sphere(int id);
void		free_sphere(t_sphere *s);

t_ray		*create_ray(t_tuple *point, t_tuple *dir);
void		free_ray(t_ray *r);
t_intersect	*intersect(t_ray *r, t_sphere *sp);
void		free_intersect(t_intersect *i);
void		print_intersect(t_intersect *i);
void		add_intersect_back(t_intersect *src, t_intersect **list);
void		free_intersect_list(t_intersect *i);
t_ray		*translate_ray(t_ray *r, double x, double y, double z);
t_ray		*scale_ray(t_ray *r, double x, double y, double z);
t_sphere	*translate_sphere(t_sphere *s, double x, double y, double z);
t_sphere	*scale_sphere(t_sphere *s, double x, double y, double z);

int		compare_double(double x, double y);
double	sq(double n);

#endif