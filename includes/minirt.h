/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:05:41 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/03 18:48:49 by wshou-xi         ###   ########.fr       */
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
}				t_tuple;

t_tuple	*create_tuple(double x, double y, double z, double w);
t_tuple	*create_point(double x, double y, double z);
t_tuple	*create_vector(double x, double y, double z);
t_tuple	*create_temp_tuple(double x, double y, double z, double w);

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*negate_tuple(t_tuple *t1);
void	print_tuple(t_tuple *t);

int	compare_double(double x, double y);

#endif