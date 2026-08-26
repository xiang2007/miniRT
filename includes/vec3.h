/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:39:18 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/29 17:49:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <stdbool.h>
# include "libft.h"

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
		};
	};
} t_vec3, t_color,	t_point3;

typedef struct s_rng_state
{
	t_xorshift32	seed;
	bool			init;
}				t_rng_state;

t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mul(t_vec3 a, double t);
t_vec3		vec_div(t_vec3 a, double t);

t_vec3		create_vec3(double a, double b, double c);

double		vec_len_sq(t_vec3 a);
double		vec_len(t_vec3 a);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
double		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		unit_vec(t_vec3 a);

t_vec3	vec_rotate(t_vec3 v, t_vec3 axis, double angle);

t_point3	sub_point(t_point3 p1, t_point3 p2);

t_vec3		vec3_rand(double min, double max);
t_vec3		rand_unit_vec3(void);
t_vec3		rand_on_hemi(const t_vec3 *normal);
double		random_double(double min, double max);
t_vec3		rand_in_unit_sphere(void);

bool		near_zero(t_vec3 *vector);

t_vec3		reflect(const t_vec3 *vec, const t_vec3 *normal);
t_vec3		refract(const t_vec3 *uv, const t_vec3 *n, double etai_over_etat);

#endif
