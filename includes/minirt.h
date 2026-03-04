/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:05:41 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/05 00:25:50 by wshou-xi         ###   ########.fr       */
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

t_tuple	*create_tuple(double x, double y, double z, double w);
t_tuple	*create_point(double x, double y, double z);
t_tuple	*create_vector(double x, double y, double z);
t_tuple	*create_temp_tuple(double x, double y, double z, double w);

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*negate_tuple(t_tuple *t1);
void	print_tuple(t_tuple *t);
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

int		compare_double(double x, double y);
double	sq(double n);

#endif