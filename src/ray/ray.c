/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/05 20:55:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/color.h"
#include "../../includes/material.h"
#include "../../includes/aabb.h"
#include <math.h>
#include <stddef.h>

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

static bool	hit_world_bvh(t_world *world, t_ray *r, double max_t,
		t_hit_dat *rec)
{
	if (!world->bvh)
		return (false);
	return (hit_bvh(world->bvh, (t_bvh_args){r, max_t, rec, NULL}));
}

/**
 * @brief Iterates through all the objects and returns true
 * if hit obj or false if not, c is shortform for closest_so_far
 *
 * @param r the ray
 * @param world world data struct
 * @param rec data struct when ray hits object
 * @return true if hit any objects or false if not
 */
bool	hit_list(t_ray *r, t_world *world, t_hit_dat *rec)
{
	t_objects	*t;
	bool		hit_anything;
	double		c;
	t_hit_dat	t_rec;

	t = world->objs;
	hit_anything = false;
	c = INFINITY;
	if (hit_world_bvh(world, r, c, rec))
	{
		hit_anything = true;
		c = rec->t;
	}
	while (t)
	{
		if (t->type == OBJ_PLANE && hit_plane(&t->plane, r, c, &t_rec) > 0)
		{
			hit_anything = true;
			c = t_rec.t;
			*rec = t_rec;
			rec->hit_obj = t;
		}
		t = t->next;
	}
	return (hit_anything);
}

/**
 * @brief Calculates the hit data from hit_list and calculates
 * the colour from it.
 *
 * @param r the ray
 * @param world the world data
 * @return the colour struct
 */
t_color	ray_color(t_ray *r, int bounce_depth, t_world *world)
{
	t_hit_dat	rec;

	rec = (t_hit_dat){0};
	if (bounce_depth <= 0)
		return (ambient_light(world));
	if (!hit_list(r, world, &rec))
		return (ambient_light(world));
	if (rec.mat && rec.mat->scatter == metal_scatter)
		return (metal_shade(&rec, world, r, bounce_depth));
	if (rec.mat && rec.mat->scatter == dielectric_scatter)
		return (dielectric_shade(&rec, world, r, bounce_depth));
	return (compute_direct_lighting(&rec, world, r));
}
