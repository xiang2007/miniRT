/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/13 10:37:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"
#include "../../includes/objects.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

/**
 * @brief Calculates the ray position in terms of distance (t)
 * Hit Point = Origin + (t * Direction)
 *
 * @param r the ray
 * @param t the distance
 * @return the position of the ray at 't' distance
 */
t_vec3	ray_pos(t_ray *r, double t)
{
	t_vec3		scaled_dir;
	t_point3	res;

	scaled_dir = vec_mul(r->vec, t);
	res = vec_add(r->point, scaled_dir);
	return (res);
}

/**
 * @brief Create a ray struct on stack memory
 *
 * @param cam_center camera position
 * @param ray_dir ray direction
 * @return the ray struct
 */
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
 * @param r the ray
 * @param world world data struct
 * @param rec data struct when ray hits object
 * @return true if hit any objects or false if not
 */
bool hit_list(t_ray *r, t_world *world, t_hit_dat *rec)
{
	t_objects	*tmp;
	bool		hit_anything;
	double		closest_so_far;
	t_hit_dat	tmp_rec;

	tmp = world->objs;
	hit_anything = false;
	closest_so_far = INFINITY;
	rec->mat = 0;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE && hit_sphere(&tmp->sphere, r, closest_so_far, &tmp_rec) > 0)
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		else if (tmp->type == OBJ_PLANE && hit_plane(&tmp->plane, r, closest_so_far, &tmp_rec) > 0)
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}

/**
 * @brief Calculates the hit data from hit_list and calculates the colour from it.
 *
 * @param r the ray
 * @param world the world data
 * @return the colour struct
 */
t_color	ray_color(t_ray *r, int bounce_depth, t_world *world)
{
	double		a;
	t_color		res;
	t_vec3		u_dir;
	t_hit_dat	rec;
	t_ray		scattered;
	t_color		attenuation;

	rec = (t_hit_dat){0};
	if (bounce_depth <= 0)
		return (create_color(0, 0, 0));
	if (hit_list(r, world, &rec))
	{
		if (rec.mat->scatter(rec.mat, r, &rec, &attenuation, &scattered))
			return (color_mul(attenuation, ray_color(&scattered, bounce_depth - 1, world)));
		return (create_color(0.0, 0.0, 0.0));
	}
	u_dir = unit_vec(r->vec);
	a = 0.5 * (u_dir.y + 1); // normalize
	res = color_add(color_mul_n(create_color(1, 1, 1), (1 - a)),
			color_mul_n(create_color(0.5, 0.7, 1.0), a)); // Sky colour
	return (res);
}
