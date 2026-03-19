/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/19 18:01:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ray_pos(t_ray r, double t)
{
	t_vec3		scaled_dir;
	t_point3	res;

	scaled_dir = scale_vec(r.vec, t);
	res = add_vec(r.point, scaled_dir);
	return (res);
}

t_ray	ray(t_point3 cam_center, t_vec3 ray_dir)
{
	t_ray	r;

	r.point = cam_center;
	r.vec = ray_dir;
	return (r);
}
