/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:40:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 17:57:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

double	vec_len_sq(t_vec3 a)
{
	return (pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0));
}

double	vec_len(t_vec3 a)
{
	return (sqrt(vec_len_sq(a)));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	unit_vec(t_vec3 a)
{
	return (vec_div(a, vec_len(a)));
}
