/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:03:26 by wshou-xi         ###   ########.fr       */
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
	if (world->bvh && hit_bvh(world->bvh, r, c, rec, NULL))
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

static t_color	all_lights(t_hit_dat *rec, t_world *w, t_ray *r)
{
	t_objects	*obj;
	t_color		result;

	result = create_color(0, 0, 0);
	obj = w->objs;
	while (obj)
	{
		if (obj->type == OBJ_LIGHT)
			result = color_add(result,
					lightning(rec, w, r, obj->light));
		obj = obj->next;
	}
	return (result);
}

/**
 * @brief For recursive materials: find point lights aligned with the
 * outgoing ray, verify visibility with a shadow ray, add specular color.
 *
 * fuzz widens the acceptance cone: 0.0 = razor-sharp mirror alignment,
 * 1.0 = accept the whole hemisphere (soft, broad highlight).
 * tint = albedo for metal, attenuation (white) for dielectric.
 */
t_color	recursive_light_hits(t_hit_dat *rec, t_world *w,
		const t_ray *outgoing, double fuzz, t_color tint)
{
	t_recurse_l_hit t;

	t.result = create_color(0, 0, 0);
	t.out_dir = unit_vec(outgoing->vec);
	t.accept_cos = 1.0 - fuzz;
	t.obj = w->objs;
	while (t.obj)
	{
		if (t.obj->type == OBJ_LIGHT)
		{
			t.light_dir = unit_vec(sub_point(t.obj->light.cords, rec->point));
			t.alignment = fmax(vec_dot(t.out_dir, t.light_dir), 0.0);
			if (t.alignment > t.accept_cos)
			{
				t.shadow_ray = ray(
						vec_add(rec->point, vec_mul(t.out_dir, 0.01)),
						t.light_dir);
				t.distance = vec_len(sub_point(t.obj->light.cords, rec->point));
				if (!shadow_hit(w, &t.shadow_ray, t.distance, rec->hit_obj))
				{
					if (fuzz < 1e-6)
						t.intensity = 1.0;
					else
						t.intensity = (t.alignment - t.accept_cos) / (1.0 - t.accept_cos);
					t.result = color_add(t.result, color_mul_n(
							color_mul(tint, t.obj->light.color),
							light_attenuation(t.obj->light, t.distance) * t.intensity));
				}
			}
		}
		t.obj = t.obj->next;
	}
	return (t.result);
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
	return (all_lights(&rec, world, r));
}
