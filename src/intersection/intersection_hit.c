/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/05/12 00:18:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include "ray.h"
#include <math.h>
#include <stdbool.h>

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

double hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec)
{
	float		t;
	float		d;
	t_point3	p0;

	d = vec_dot(p->normal, ray->vec);
	if (fabs(d) <= __DBL_EPSILON__)
		return (-1);
	p0 = vec_sub(p->center, ray->point);
	t = vec_dot(p0, p->normal) / d;
	if (t <= 0.0 || t >= r_max)
		return (-1);
	rec->t = t;
	rec->normal = unit_vec(p->normal);
	return (t);
}
