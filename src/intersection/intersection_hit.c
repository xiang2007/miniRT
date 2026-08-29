/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 10:46:19 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vec3.h"
#include <stdio.h>
#include "material.h"

void	set_face_normal(const t_ray *r, const t_vec3 *out_norm, t_hit_dat *rec)
{
	rec->front_face = vec_dot(r->vec, *out_norm) < 0.001;
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

static t_color	plane_color(const t_plane *p, const t_vec3 *point,
		const t_vec3 *normal)
{
	t_lambertian	*lam;
	t_vec3			tangent;
	t_vec3			bitangent;
	t_vec3			rel;
	double			u;
	double			v;

	lam = (t_lambertian *)p->material;
	if (!lam || lam->base.scatter != lambertian_scatter
		|| lam->checker_size <= 0.0)
		return (p->color);
	if (fabs(normal->y) < 0.99)
		tangent = unit_vec(vec_cross(*normal, create_vec3(0, 1, 0)));
	else
		tangent = unit_vec(vec_cross(*normal, create_vec3(1, 0, 0)));
	bitangent = vec_cross(*normal, tangent);
	rel = vec_sub(*point, p->center);
	u = vec_dot(rel, tangent);
	v = vec_dot(rel, bitangent);
	if ((((int)floor(u / lam->checker_size))
			+ ((int)floor(v / lam->checker_size))) % 2 == 0)
		return (lam->albedo);
	return (lam->checker_color);
}

t_color	lerp_colour(t_color base, t_color tint, float strength)
{
	t_color	final;

	final.r = (base.r * (1.0 - strength)) + (tint.r * strength);
	final.g = (base.g * (1.0 - strength)) + (tint.g * strength);
	final.b = (base.b * (1.0 - strength)) + (tint.b * strength);
	return (final);
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
double	hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec)
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
	set_face_normal(ray, &normal, rec);
	rec->mat = p->material;

	t_vec3	helper = (fabs(rec->normal.y) > 0.999) ? create_vec3(1, 0, 0) : create_vec3(0, 1, 0);
	t_vec3	u_axis = unit_vec(vec_cross(helper, rec->normal));
	t_vec3	v_axis = unit_vec(vec_cross(rec->normal, u_axis));
	t_vec3 hit_vector = vec_sub(rec->point, p->center);
	float local_u = vec_dot(hit_vector, u_axis);
	float local_v = vec_dot(hit_vector, v_axis);
	float	scale = 1.0;
	int		check_u = (int)floor(local_u * scale);
	int		check_v = (int)floor(local_v * scale);
	if (abs((check_u + check_v) % 2) == 0)
	{	
		rec->color = lerp_colour(p->color, (t_color) {.r = 0.1, .g = 0.1, .b = 0.1}, 0.3);
	}
	else
		rec->color = plane_color(p, &rec->point, &normal);
	return (t);
}

double	hit_cap(t_cylinder_args *args, const t_vec3 *cap_center,
		const t_vec3 *normal)
{
	double	denom;
	double	t;
	t_vec3	hit_point;

	denom = vec_dot(args->ray->vec, *normal);
	if (fabs(denom) < 1e-8)
		return (-1.0);
	t = vec_dot(vec_sub(*cap_center, args->ray->point), *normal) / denom;
	if (t <= 0.001 || t >= args->r_max)
		return (-1.0);
	hit_point = ray_pos(args->ray, t);
	if (vec_len_sq(vec_sub(hit_point, *cap_center))
		> args->cy->radius * args->cy->radius)
		return (-1.0);
	return (t);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray, double r_max, t_hit_dat *rec)
{
	t_cylinder_hit	c;
	t_cylinder_args	a;

	a.cy = cy;
	a.ray = ray;
	a.r_max = r_max;
	a.rec = rec;
	hit_cylinder_tube(&c, &a);
	hit_cylinder_tube2(&c, &a);
	hit_cylinder_caps(&c, &a);
	if (c.t_best < 0.0)
		return (-1.0);
	rec->t = c.t_best;
	rec->point = ray_pos(ray, c.t_best);
	rec->color = cy->color;
	rec->mat = cy->material;
	if (c.t_best == c.t_tube)
	{
		c.p = vec_add(cy->center, vec_mul(cy->axis, c.m));
		c.outward_normal = vec_div(vec_sub(rec->point, c.p), cy->radius);
	}
	set_face_normal(ray, &c.outward_normal, rec);
	return (c.t_best);
}
