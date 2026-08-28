/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/26 23:58:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"
#include "../../includes/objects.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include "../../includes/aabb.h"
#include "minirt.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stddef.h>

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

static void	lightning_helper(t_lightning *l, t_hit_dat *rec, t_ray *r,
		t_light light)
{
	double	fuzz;

	fuzz = material_fuzz(rec->mat);
	l->brightness = fmax(vec_dot(rec->normal, l->light_dir), 0.0);
	l->brightness *= light_attenuation(light, l->light_distance);
	l->light_in = vec_mul(l->light_dir, -1.0);
	l->reflected = reflect(&l->light_in, &rec->normal);
	if (fuzz > 0.0)
		l->reflected = vec_add(l->reflected, vec_mul(rand_unit_vec3(), fuzz));
	l->reflected = unit_vec(l->reflected);
	l->view_dir = unit_vec(vec_mul(r->vec, -1.0));
	/* inside lightning(), dielectric only */
	if (rec->mat && rec->mat->scatter == dielectric_scatter)
		l->specular = pow(fmax(1.0 - vec_dot(rec->normal, l->view_dir), 0.0),
				5.0);
	else
		l->specular = pow(fmax(vec_dot(l->view_dir, l->reflected), 0.0), 32.0);
	l->specular *= light_attenuation(light, l->light_distance);
}

t_color	lightning(t_hit_dat *rec, t_world *w, t_ray *r, t_light light)
{
	t_lightning	l;

	l = (t_lightning){0};
	l.shadow_ori = vec_add(rec->point, vec_mul(rec->normal, 0.001));
	l.light_dir = unit_vec(sub_point(light.cords, rec->point));
	l.light_distance = vec_len(sub_point(light.cords, rec->point));
	l.shadow_ray = ray(l.shadow_ori, l.light_dir);
	if (!shadow_hit(w, &l.shadow_ray, l.light_distance, rec->hit_obj))
	{
		lightning_helper(&l, rec, r, light);
		l.result = color_add(
				color_mul_n(material_albedo(rec->mat, rec->color), l.brightness),
				color_mul_n(light.color, l.specular));
		return (l.result);
	}
	return (create_color(0, 0, 0));
}
