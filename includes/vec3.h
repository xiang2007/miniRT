/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:39:18 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/05/11 17:29:17 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

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

t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_mul(t_vec3 a, double t);
t_vec3	vec_div(t_vec3 a, double t);

t_vec3	create_vec3(double a, double b, double c);

double	vec_len_sq(t_vec3 a);
double	vec_len(t_vec3 a);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	unit_vec(t_vec3 a);

t_point3 sub_point(t_point3 p1, t_point3 p2);

t_vec3	vec3_rand(double min, double max);

#endif
