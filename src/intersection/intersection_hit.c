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
	if (root <= 0 || r_max <= root) // less than zero or larger than the current smallest root not acceptable
	{
		root = (h + sqrt(d)) / a;
		if (root <= 0 || r_max <= root)
			return (0);
	}
	rec->t = root;
	rec->normal = unit_vec(vec_sub(ray_pos(r, root), sp->point)); // calculates the normal in unit length
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
	return (t);
}
