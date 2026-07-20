/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/06/11 02:51:52 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/objects.h"
#include "../../includes/ray.h"
#include <math.h>
#include <stdbool.h>

void	set_face_normal(const t_ray *r, const t_vec3 *outward_normal, t_hit_dat *rec)
{
	// Sets the hit record normal vector.
	// NOTE: the parameter `outward_normal` is assumed to have unit length.
	rec->front_face = vec_dot(r->vec, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec_mul(*outward_normal, -1.0);
}

// TODO: might need more description

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
	t_vec3	ori_center;
	t_vec3	outward_normal;
	double	a;
	double	h;
	double	c;
	double	d;
	double	root;

	ori_center = vec_sub(sp->point, r->point);
	a = vec_len_sq(r->vec);
	h = vec_dot(r->vec, ori_center);
	c = vec_len_sq(ori_center) - pow(sp->radius, 2.0);
	d = pow(h, 2.0) - a * c;
	if (d < 0)
		return (-1);
	root = (h - sqrt(d)) / a;
	if (root <= 0.001 || r_max <= root) // less than zero or larger than the current smallest root not acceptable
	{
		root = (h + sqrt(d)) / a;
		if (root <= 0.001 || r_max <= root)
			return (0);
	}
	rec->t = root;
	rec->point = ray_pos(r, root);
	outward_normal = vec_div(vec_sub(rec->point, sp->point), sp->radius);
	set_face_normal(r, &outward_normal, rec);
	// rec->normal = unit_vec(vec_sub(ray_pos(r, root), sp->point)); // calculates the normal in unit length
	rec->mat = sp->material;
	return (root);
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
	rec->normal = normal;
	rec->point = ray_pos(ray, t);
	return (t);
}
