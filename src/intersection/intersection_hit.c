/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 07:48:30 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/objects.h"
#include "../../includes/ray.h"
#include <math.h>
#include <stdbool.h>

void	set_face_normal(const t_ray *r, const t_vec3 *out_norm, t_hit_dat *rec)
{
	rec->front_face = vec_dot(r->vec, *out_norm) < 0;
	if (rec->front_face)
		rec->normal = *out_norm;
	else
		rec->normal = vec_mul(*out_norm, -1.0);
}

/**
 * @brief Calculates whether the ray hits the sphere
 *
 * @param sp sphere struct
 * @param r ray struct
 * @param r_max closest hit point I think
 * @param rec record hit struct
 * @return root value
 */
double	hit_sphere(t_sphere *sp, t_ray *r, double r_max, t_hit_dat *rec)
{
	t_hit_sphere	dat;

	dat.ori_center = vec_sub(sp->point, r->point);
	dat.a = vec_len_sq(r->vec);
	dat.h = vec_dot(r->vec, dat.ori_center);
	dat.c = vec_len_sq(dat.ori_center) - pow(sp->radius, 2.0);
	dat.d = (dat.h * dat.h) - dat.a * dat.c;
	if (dat.d < 0)
		return (-1);
	dat.root = (dat.h - sqrt(dat.d)) / dat.a;
	if (dat.root <= 0.001 || r_max <= dat.root)
	{
		dat.root = (dat.h + sqrt(dat.d)) / dat.a;
		if (dat.root <= 0.001 || r_max <= dat.root)
			return (0);
	}
	rec->t = dat.root;
	rec->point = ray_pos(r, dat.root);
	rec->color = sp->color;
	dat.outward_normal = vec_div(vec_sub(rec->point, sp->point), sp->radius);
	set_face_normal(r, &dat.outward_normal, rec);
	rec->mat = sp->material;
	return (dat.root);
}

/**
 * @brief Calculates whether the ray hits the plane
 *
 * @param p the plane struct
 * @param ray the ray struct
 * @param r_max closest hit I think
 * @param rec the record hit struct
 * @return the root value
 */
double hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec)
{
	double	t;
	double	d;
	t_vec3	p0;
	t_vec3	normal;

	normal = unit_vec(p->normal);
	d = vec_dot(normal, ray->vec);
	if (fabs(d) < __DBL_EPSILON__)
		return (-1);
	p0 = vec_sub(p->center, ray->point);
	t = vec_dot(p0, normal) / d;
	if (t <= __DBL_EPSILON__ || t >= r_max)
		return (-1);
	rec->t = t;
	rec->point = ray_pos(ray, t);
	rec->color = p->color;
	set_face_normal(ray, &normal, rec);
	rec->mat = 0;
	return (t);
}
