/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:27:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:15:58 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"

/**
 * @brief Creates a vector struct with numbers from the parameter
 *
 * @param a the x coordinate
 * @param b the y coordinate
 * @param c the z coordinate
 * @return the vector
 */
t_vec3	create_vec3(double a, double b, double c)
{
	t_vec3	res;

	res.x = a;
	res.y = b;
	res.z = c;
	return (res);
}

t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	k;
	t_vec3	cross;
	double	cos_a;
	double	sin_a;
	double	dot;

	k = unit_vec3(axis);
	cos_a = cos(angle);
	sin_a = sin(angle);
	dot = vec3_dot(k, v);
	cross = vec3_cross(k, v);
	return (vec3_add(vec3_add(vec3_mul(v, cos_a), vec3_mul(cross, sin_a)),
			vec3_mul(k, dot * (1.0 - cos_a))));
}

t_vec3	get_object_right(t_vec3 obj_axis)
{
	t_vec3	world_up;

	world_up = create_vec3(0.0, 1.0, 0.0);
	if (fabs(obj_axis.y) > 0.99)
		world_up = create_vec3(1.0, 0.0, 0.0);
	return (unit_vec3(vec3_cross(world_up, obj_axis)));
}

t_vec3	get_object_up(t_vec3 obj_axis, t_vec3 obj_right)
{
	return (unit_vec3(vec3_cross(obj_axis, obj_right)));
}
