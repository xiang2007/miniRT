/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 19:30:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"
#include "../../includes/ray.h"

t_aabb	surround_box(t_aabb a, t_aabb b)
{
	t_aabb res;

	res.min.x = fmin(a.min.x, b.min.x);
	res.min.y = fmin(a.min.y, b.min.y);
	res.min.z = fmin(a.min.z, b.min.z);
	res.max.x = fmax(a.max.x, b.max.x);
	res.max.y = fmax(a.max.y, b.max.y);
	res.max.z = fmax(a.max.z, b.max.z);
	return (res);
}

t_aabb	build_box(t_objects *o)
{
	t_aabb		box = {0};

	if (o->type == OBJ_SPHERE)
	{
		box.min = create_vec3(o->sphere.point.x - o->sphere.radius,
			o->sphere.point.y - o->sphere.radius,
			o->sphere.point.z - o->sphere.radius);
		box.max = create_vec3(o->sphere.point.x + o->sphere.radius,
			o->sphere.point.y + o->sphere.radius,
			o->sphere.point.z + o->sphere.radius);
	}
	return (box);
}

double	get_box_point_n(t_aabb *aabb, int n, int min, int max)
{
	if (!aabb || n < 1 || n > 3)
		return (-1);
	if (min)
	{
		if (n == 1)
			return (aabb->min.x);
		else if (n == 2)
			return (aabb->min.y);
		else
			return (aabb->min.z);
	}
	if (max)
	{
		if (n == 1)
			return (aabb->max.x);
		else if (n == 2)
			return (aabb->max.y);
		else
			return (aabb->max.z);
	}
	return (-1);
}

void	swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static bool	slab_hit(double origin, double direction, double min,
			double max, double *t_min, double *t_max)
{
	double	inv_d;
	double	t0;
	double	t1;

	if (fabs(direction) < 1e-12)
		return (origin >= min && origin <= max);
	inv_d = 1.0 / direction;
	t0 = (min - origin) * inv_d;
	t1 = (max - origin) * inv_d;
	if (inv_d < 0.0)
		swap_double(&t0, &t1);
	if (t0 > *t_min)
		*t_min = t0;
	if (t1 < *t_max)
		*t_max = t1;
	return (*t_max > *t_min);
}

bool	aabb_hit(t_aabb *box, t_ray *ray, double t_min, double t_max)
{
	if (!box || !ray)
		return (false);
	if (!slab_hit(ray->point.x, ray->vec.x, box->min.x, box->max.x,
			&t_min, &t_max))
		return (false);
	if (!slab_hit(ray->point.y, ray->vec.y, box->min.y, box->max.y,
			&t_min, &t_max))
		return (false);
	return (slab_hit(ray->point.z, ray->vec.z, box->min.z, box->max.z,
		&t_min, &t_max));
}
