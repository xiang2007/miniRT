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

#include <float.h>
#include <stdbool.h>

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

/**
 * @brief Iterates through all the objects and returns true if hit obj or false if not
 *
 * @param r
 * @param world
 * @param rec
 * @return
 */
bool hit_list(t_ray *r, t_world *world, t_hit_dat *rec)
{
	t_objects	*tmp;
	bool		hit_anything;
	double		closest_so_far;
	t_hit_dat	tmp_rec;

	tmp = world->objs;
	hit_anything = false;
	closest_so_far = DBL_MAX;
	while (tmp)
	{
		if (hit_sphere(&tmp->sphere, r, closest_so_far, &tmp_rec) > 0)
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}

t_color	ray_color(t_ray *r, t_world *world)
{
	double		t;
	double		a;
	t_color		res;
	t_vec3		u_dir;
	t_hit_dat	rec;

	rec = (t_hit_dat){0};
	t = hit_list(r, world, &rec);
	if (t > 0.0)
		return (color_mul_n(create_color(rec.normal.r + 1, rec.normal.g + 1, rec.normal.b + 1), 0.5)); // Normals Shading
	u_dir = unit_vec(r->vec);
	a = 0.5 * (u_dir.y + 1); // normalize
	res = color_add(color_mul_n(create_color(1, 1, 1), (1 - a)),
			color_mul_n(create_color(0.5, 0.7, 1), a)); // Sky colour
	return (res);
}
