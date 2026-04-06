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

#include "vec3.h"
#include "color.h"
#include "objects.h"
#include "ray.h"

t_vec3	ray_pos(t_ray *r, double t)
{
	t_vec3		scaled_dir;
	t_point3	res;

	scaled_dir = vec_mul(r->vec, t);
	res = vec_add(r->point, scaled_dir);
	return (res);
}

t_ray	ray(t_point3 cam_center, t_vec3 ray_dir)
{
	t_ray	r;

	r.point = cam_center;
	r.vec = ray_dir;
	return (r);
}

t_color	ray_color(t_ray *r, t_sphere *sp)
{
	double	t;
	double	a;
	t_color	res;
	t_vec3	u_dir;
	t_vec3	n;

	t = hit_sphere(sp, r);
	if (t > 0.0)
	{
		n = unit_vec(vec_sub(ray_pos(r, t), sp->point));
		return (color_mul_n(create_color(n.x + 1, n.y + 1, n.z + 1), 0.5));
	}
	u_dir = unit_vec(r->vec);
	a = 0.5 * (u_dir.y + 1); // normalize
	res = color_add(color_mul_n(create_color(1, 1, 1), (1 - a)),
			color_mul_n(create_color(0.5, 0.7, 1), a));
	return (res);
}
