/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 18:57:28 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"
#include "../../includes/objects.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include "../../includes/aabb.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stddef.h>

static double	material_fuzz(const t_material *mat)
{
	t_metal	*metal;

	if (mat && mat->scatter == metal_scatter)
	{
		metal = (t_metal *)mat;
		return (metal->fuzziness);
	}
	return (0.0);
}

static t_color	ambient_light(t_world *w)
{
	t_objects	*obj;

	obj = w->objs;
	while (obj)
	{
		if (obj->type == OBJ_AMBIENT)
			return (color_mul_n(obj->ambient.color, obj->ambient.ratio));
		obj = obj->next;
	}
	return (create_color(0, 0, 0));
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

static bool	shadow_hit(t_world *w, t_ray *ray, double t_max, t_objects *skip)
{
	t_hit_dat	rec;
	t_objects	*tmp;

	rec = (t_hit_dat){0};
	if (w->bvh && hit_bvh(w->bvh, ray, t_max, &rec, skip))
		return (true);
	tmp = w->objs;
	while (tmp)
	{
		if (tmp->type == OBJ_PLANE && tmp != skip
			&& hit_plane(&tmp->plane, ray, t_max, &rec) > 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

/**
 * @brief Iterates through all the objects and returns true
 * if hit obj or false if not
 *
 * @param r the ray
 * @param world world data struct
 * @param rec data struct when ray hits object
 * @return true if hit any objects or false if not
 */
bool	hit_list(t_ray *r, t_world *world, t_hit_dat *rec)
{
	t_objects	*tmp;
	bool		hit_anything;
	double		closest_so_far;
	t_hit_dat	tmp_rec;

	tmp = world->objs;
	hit_anything = false;
	closest_so_far = INFINITY;
	if (world->bvh && hit_bvh(world->bvh, r, closest_so_far, rec, NULL))
	{
		hit_anything = true;
		closest_so_far = rec->t;
	}
	while (tmp)
	{
		if (tmp->type == OBJ_PLANE
			&& hit_plane(&tmp->plane, r, closest_so_far, &tmp_rec) > 0)
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
			rec->hit_obj = tmp;	/* NEW: planes aren't in the BVH */
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}

static t_color	material_albedo(const t_material *mat, t_color fallback)
{
	t_lambertian	*lam;

	if (!mat)
		return (fallback);
	if (mat->scatter == dielectric_scatter)
		return (create_color(1.0, 1.0, 1.0));
	lam = (t_lambertian *)mat;
	return (lam->albedo);
}

static t_color	lightning(t_hit_dat *rec, t_world *w, t_ray *r, t_light light)
{
	t_lightning	l;

	l = (t_lightning){0};
	l.shadow_ori = vec_add(rec->point, vec_mul(rec->normal, 0.001));
	l.light_dir = unit_vec(sub_point(light.cords, rec->point));
	l.light_distance = vec_len(sub_point(light.cords, rec->point));
	l.shadow_ray = ray(l.shadow_ori, l.light_dir);
	if (!shadow_hit(w, &l.shadow_ray, l.light_distance, rec->hit_obj))
	{
		l.brightness = fmax(vec_dot(rec->normal, l.light_dir), 0.0);
		l.brightness *= light.brightness_ratio;
		l.light_in = vec_mul(l.light_dir, -1.0);
		l.reflected = reflect(&l.light_in, &rec->normal);
		if (material_fuzz(rec->mat) > 0.0)
			l.reflected = vec_add(l.reflected,
					vec_mul(rand_unit_vec3(), material_fuzz(rec->mat)));
		l.reflected = unit_vec(l.reflected);
		l.view_dir = unit_vec(vec_mul(r->vec, -1.0));
		/* inside lightning(), dielectric only */
		if (rec->mat && rec->mat->scatter == dielectric_scatter)
			l.specular = pow(fmax(1.0 - vec_dot(rec->normal, l.view_dir), 0.0), 5.0);
		else
			l.specular = pow(fmax(vec_dot(l.view_dir, l.reflected), 0.0), 32.0);
		l.specular *= light.brightness_ratio;
		l.result = color_add(
				color_mul_n(material_albedo(rec->mat, rec->color), l.brightness),
				color_mul_n(light.color, l.specular));
		l.result.r = fmin(l.result.r, 1.0);
		l.result.g = fmin(l.result.g, 1.0);
		l.result.b = fmin(l.result.b, 1.0);
		return (l.result);
	}
	return (create_color(0, 0, 0));
}

static t_color	all_lights(t_hit_dat *rec, t_world *w, t_ray *r)
{
	t_objects	*obj;
	t_color		result;

	result = ambient_light(w);
	obj = w->objs;
	while (obj)
	{
		if (obj->type == OBJ_LIGHT)
			result = color_add(result,
					lightning(rec, w, r, obj->light));
		obj = obj->next;
	}
	result.r = fmin(result.r, 1.0);
	result.g = fmin(result.g, 1.0);
	result.b = fmin(result.b, 1.0);
	return (result);
}

static t_color	background_gradient(const t_ray *r)
{
	double	a;
	t_vec3	u_dir;

	u_dir = unit_vec(r->vec);
	a = 0.5 * (u_dir.y + 1.0);
	return (color_add(
			color_mul_n(create_color(1.0, 1.0, 1.0), (1.0 - a)),
			color_mul_n(create_color(0.5, 0.7, 1.0), a)));
}

static t_color	clamp_color(t_color c)
{
	c.r = fmin(c.r, 1.0);
	c.g = fmin(c.g, 1.0);
	c.b = fmin(c.b, 1.0);
	return (c);
}

/**
 * @brief For recursive materials: find point lights aligned with the
 * outgoing ray, verify visibility with a shadow ray, add specular color.
 *
 * fuzz widens the acceptance cone: 0.0 = razor-sharp mirror alignment,
 * 1.0 = accept the whole hemisphere (soft, broad highlight).
 * tint = albedo for metal, attenuation (white) for dielectric.
 */
static t_color	recursive_light_hits(t_hit_dat *rec, t_world *w,
		const t_ray *outgoing, double fuzz, t_color tint)
{
	t_objects	*obj;
	t_color		result;
	t_vec3		out_dir;
	t_vec3		light_dir;
	t_ray		shadow_ray;
	double		alignment;
	double		accept_cos;
	double		intensity;
	double		distance;

	result = create_color(0, 0, 0);
	out_dir = unit_vec(outgoing->vec);
	accept_cos = 1.0 - fuzz;			/* dynamic threshold */
	obj = w->objs;
	while (obj)
	{
		if (obj->type == OBJ_LIGHT)
		{
			light_dir = unit_vec(sub_point(obj->light.cords, rec->point));
			alignment = fmax(vec_dot(out_dir, light_dir), 0.0);
			if (alignment > accept_cos)
			{
				shadow_ray = ray(
						vec_add(rec->point, vec_mul(out_dir, 0.01)),
						light_dir);
				distance = vec_len(sub_point(obj->light.cords, rec->point));
				if (!shadow_hit(w, &shadow_ray, distance, rec->hit_obj))
				{
					if (fuzz < 1e-6)
						intensity = 1.0;	/* perfect mirror: exact hit */
					else
						intensity = (alignment - accept_cos) / (1.0 - accept_cos);
					result = color_add(result, color_mul_n(
							color_mul(tint, obj->light.color),
							obj->light.brightness_ratio * intensity));
				}
			}
		}
		obj = obj->next;
	}
	return (result);
}

static t_color	metal_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth)
{
	t_metal	*metal;
	t_vec3	reflected;		/* perfect mirror direction */
	t_vec3	fuzzy;			/* fuzzy = perfect + fuzz * rand_in_unit_sphere */
	t_ray	scattered;
	t_color	bounced;
	t_color	light_hits;
	double	fuzz;

	metal = (t_metal *)rec->mat;
	fuzz = fmin(fmax(metal->fuzziness, 0.0), 1.0);

	/* 1. fuzzy scatter */
	reflected = reflect(&r->vec, &rec->normal);
	fuzzy = vec_add(reflected, vec_mul(rand_in_unit_sphere(), fuzz));

	/* 2. absorption: scattered below the surface is discarded */
	if (vec_dot(fuzzy, rec->normal) <= 0.0)
		return (create_color(0, 0, 0));
	fuzzy = unit_vec(fuzzy);
	scattered = ray(rec->point, fuzzy);

	/* 3. recursive reflection of the scene, tinted by the metal albedo */
	bounced = color_mul(metal->albedo, ray_color(&scattered, depth - 1, w));

	/* 4. visible point-light reflections (alignment cone + shadow rays) */
	light_hits = recursive_light_hits(rec, w, &scattered, fuzz, metal->albedo);
	return (clamp_color(color_add(color_add(bounced, light_hits), ambient_light(w))));
}

static t_color	dielectric_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth)
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
	bounced = color_mul(*args.attenuation, ray_color(args.scattered, depth - 1, w));

	/* visible point lights through the glass: smooth → tight alignment cone */
	light_hits = recursive_light_hits(rec, w, args.scattered, 0.0, *args.attenuation);
	return (clamp_color(color_add(color_add(bounced, light_hits), ambient_light(w))));
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
		return (create_color(0, 0, 0));
	if (!hit_list(r, world, &rec))
		return (background_gradient(r));
	if (rec.mat && rec.mat->scatter == metal_scatter)
		return (metal_shade(&rec, world, r, bounce_depth));
	if (rec.mat && rec.mat->scatter == dielectric_scatter)
		return (dielectric_shade(&rec, world, r, bounce_depth));
	return (all_lights(&rec, world, r));	/* lambertian + planes (mat == NULL): unchanged */
}
