/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 10:53:08 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"
#include "../../includes/objects.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include "../../includes/aabb.h"
#include "minirt.h"

t_color	metal_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth)
{
	t_metal_shade t;

	t.metal = (t_metal *)rec->mat;
	t.fuzz = fmin(fmax(t.metal->fuzziness, 0.0), 1.0);

	/* 1. fuzzy scatter */
	t.reflected = reflect(&r->vec, &rec->normal);
	t.fuzzy = vec_add(t.reflected, vec_mul(rand_in_unit_sphere(), t.fuzz));
	/* 2. absorption: scattered below the surface is discarded */
	if (vec_dot(t.fuzzy, rec->normal) <= 0.0)
		return (create_color(0, 0, 0));
	t.fuzzy = unit_vec(t.fuzzy);
	t.scattered = ray(vec_add(rec->point, vec_mul(t.fuzzy, 0.001)), t.fuzzy);
	/* 3. recursive reflection of the scene, tinted by the metal albedo */
	t.bounced = color_mul(t.metal->albedo,
		ray_color(&t.scattered, depth - 1, w));
	/* 4. visible point-light reflections (alignment cone + shadow rays) */
	t.light_hits = recursive_light_hits(rec, w, &t.scattered,
			t.fuzz, t.metal->albedo);
	return (color_add(t.bounced, t.light_hits));
}

t_color	dielectric_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth)
{
	t_scatter_args	args;
	t_color			bounced;
	t_color			light_hits;

	args = (t_scatter_args){0};
	args.self = rec->mat;
	args.in = r;
	args.rec = rec;
	args.attenuation = &(t_color){0};
	args.scattered = &(t_ray){0};
	if (!rec->mat->scatter(&args))
		return (create_color(0, 0, 0));
	/* recursive transmission/reflection of the scene (attenuation = white) */
	bounced = color_mul(*args.attenuation,
			ray_color(args.scattered, depth - 1, w));
	/* point lights through the glass: small cone so they aren't razor-missed */
	light_hits = recursive_light_hits(rec, w, args.scattered,
			DIELECTRIC_FUZZ, *args.attenuation);
	return (color_add(bounced, light_hits));
}

bool	shadow_hit(t_world *w, t_ray *ray, double t_max, t_objects *skip)
{
	t_objects	*t;
	t_hit_dat	rec;

	t = w->objs;
	while (t)
	{
		if (t != skip && !material_is_transparent(t))
		{
			rec = (t_hit_dat){0};
			if (t->type == OBJ_SPHERE
				&& hit_sphere(&t->sphere, ray, t_max, &rec) > 0)
				return (true);
			if (t->type == OBJ_CYLINDER
				&& hit_cylinder(&t->cylinder, ray, t_max, &rec) > 0)
				return (true);
			if (t->type == OBJ_PLANE
				&& hit_plane(&t->plane, ray, t_max, &rec) > 0)
				return (true);
		}
		t = t->next;
	}
	return (false);
}