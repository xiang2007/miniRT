/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:21:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/12 13:55:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	add_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	sub_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3	neg_vec(t_vec3 a)
{
	t_vec3	res;

	res.x = -a.x;
	res.y = -a.y;
	res.z = -a.z;
	return (res);
}

t_vec3	scale_vec(t_vec3 a, double t)
{
	t_vec3	res;

	res.x = a.x * t;
	res.y = a.y * t;
	res.z = a.z * t;
	return (res);
}

t_vec3	div_vec(t_vec3 a, double t)
{
	t_vec3	res;
	double	inv;

	inv = (1.0 / t);
	res.x = a.x * inv;
	res.y = a.y * inv;
	res.z = a.z * inv;
	return (res);
}
