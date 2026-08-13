
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 12:03:30 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/objects.h"
#include "../../includes/ray.h"
#include "material.h"
#include <math.h>
#include <stdbool.h>

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
	rec->color = p->color;
	set_face_normal(ray, &normal, rec);
	rec->mat = p->material;
	return (t);
}

static double	hit_cap(t_cylinder *cy, t_ray *ray, double r_max,
		const t_vec3 *cap_center, const t_vec3 *normal)
{
	double	denom;
	double	t;
	t_vec3	hit_point;

	denom = vec_dot(ray->vec, *normal);
	if (fabs(denom) < 1e-8)
		return (-1.0);
	t = vec_dot(vec_sub(*cap_center, ray->point), *normal) / denom;
	if (t <= 0.001 || t >= r_max)
		return (-1.0);
	hit_point = ray_pos(ray, t);
	if (vec_len_sq(vec_sub(hit_point, *cap_center))
		> cy->radius * cy->radius)
		return (-1.0);
	return (t);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray, double r_max, t_hit_dat *rec)
{
	t_vec3	X;
	t_vec3	P;
	t_vec3	half_axis;
	t_vec3	top_center;
	t_vec3	bot_center;
	t_vec3	neg_axis;
	t_vec3	outward_normal;
	double	a;
	double	b;
	double	c;
	double	d;
	double	root;
	double	m;
	double	D_dot_V;
	double	X_dot_V;
	double	t_tube;
	double	t_top;
	double	t_bot;
	double	t_best;

	half_axis = vec_mul(cy->axis, cy->height / 2.0);
	top_center = vec_add(cy->center, half_axis);
	bot_center = vec_sub(cy->center, half_axis);
	neg_axis = vec_mul(cy->axis, -1.0);

	/* --- tube --- */
	X = vec_sub(ray->point, cy->center);
	D_dot_V = vec_dot(ray->vec, cy->axis);
	X_dot_V = vec_dot(X, cy->axis);
	a = vec_dot(ray->vec, ray->vec) - (D_dot_V * D_dot_V);
	b = 2.0 * (vec_dot(ray->vec, X) - (D_dot_V * X_dot_V));
	c = vec_dot(X, X) - (X_dot_V * X_dot_V) - (cy->radius * cy->radius);
	d = (b * b) - (4 * a * c);

	t_tube = -1.0;
	m = 0;
	if (d >= 0.0 && fabs(a) > 1e-12)
	{
		root = (-b - sqrt(d)) / (2.0 * a);
		if (root < 0.01 || root > r_max)
		{
			root = (-b + sqrt(d)) / (2.0 * a);
			if (root < 0.01 || root > r_max)
				root = -1.0;
		}
		if (root > 0.0)
		{
			m = (D_dot_V * root) + X_dot_V;
			if (m < -(cy->height / 2.0) || m > (cy->height / 2.0))
			{
				root = (-b + sqrt(d)) / (2.0 * a);
				if (root < 0.01 || root > r_max)
					root = -1.0;
				else
				{
					m = (D_dot_V * root) + X_dot_V;
					if (m < -(cy->height / 2.0) || m > (cy->height / 2.0))
						root = -1.0;
				}
			}
		}
		t_tube = root;
	}

	/* --- disk caps --- */
	t_top = hit_cap(cy, ray, r_max, &top_center, &cy->axis);
	t_bot = hit_cap(cy, ray, r_max, &bot_center, &neg_axis);

	t_best = t_tube;
	outward_normal = create_vec3(0, 0, 0);
	if (t_top > 0.0 && (t_best < 0.0 || t_top < t_best))
	{
		t_best = t_top;
		outward_normal = cy->axis;
	}
	if (t_bot > 0.0 && (t_best < 0.0 || t_bot < t_best))
	{
		t_best = t_bot;
		outward_normal = neg_axis;
	}
	if (t_best < 0.0)
		return (-1.0);

	rec->t = t_best;
	rec->point = ray_pos(ray, t_best);
	rec->color = cy->color;
	rec->mat = cy->material;
	if (t_best == t_tube)
	{
		P = vec_add(cy->center, vec_mul(cy->axis, m));
		outward_normal = vec_div(vec_sub(rec->point, P), cy->radius);
	}
	set_face_normal(ray, &outward_normal, rec);
	return (t_best);
}