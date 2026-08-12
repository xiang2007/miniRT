/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 11:33:50 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"
#include "../../includes/ray.h"
#include "vec3.h"

t_aabb	surround_box(t_aabb a, t_aabb b)
{
	t_aabb	res;

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
	t_aabb	box;
	t_vec3	half_axis;
	t_vec3	e1;
	t_vec3	e2;

	box.max = create_vec3(0, 0, 0);
	box.min = create_vec3(0, 0, 0);
	if (o->type == OBJ_SPHERE)
	{
		box.min = create_vec3(o->sphere.point.x - o->sphere.radius,
				o->sphere.point.y - o->sphere.radius,
				o->sphere.point.z - o->sphere.radius);
		box.max = create_vec3(o->sphere.point.x + o->sphere.radius,
				o->sphere.point.y + o->sphere.radius,
				o->sphere.point.z + o->sphere.radius);
	}
	else if (o->type == OBJ_CYLINDER)
	{
		if (vec_len_sq(o->cylinder.axis) > 0.0)
			half_axis = vec_mul(unit_vec(o->cylinder.axis),
					o->cylinder.height / 2.0);
		else
			half_axis = create_vec3(0, 0, 0);
		e1 = vec_add(o->cylinder.center, half_axis);
		e2 = vec_sub(o->cylinder.center, half_axis);
		box.min = create_vec3(fmin(e1.x, e2.x) - o->cylinder.radius,
				fmin(e1.y, e2.y) - o->cylinder.radius,
				fmin(e1.z, e2.z) - o->cylinder.radius);
		box.max = create_vec3(fmax(e1.x, e2.x) + o->cylinder.radius,
				fmax(e1.y, e2.y) + o->cylinder.radius,
				fmax(e1.z, e2.z) + o->cylinder.radius);
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

static bool	slab_hit(t_slab_args args)
{
	double	inv_d;
	double	t0;
	double	t1;

	if (fabs(args.direction) < 1e-12)
		return (args.origin >= args.min && args.origin <= args.max);
	inv_d = 1.0 / args.direction;
	t0 = (args.min - args.origin) * inv_d;
	t1 = (args.max - args.origin) * inv_d;
	if (inv_d < 0.0)
		swap_double(&t0, &t1);
	if (t0 > *args.t_min)
		*args.t_min = t0;
	if (t1 < *args.t_max)
		*args.t_max = t1;
	return (*args.t_max > *args.t_min);
}

bool	aabb_hit(t_aabb *box, t_ray *ray, double t_min, double t_max)
{
	if (!box || !ray)
		return (false);
	if (!slab_hit((t_slab_args){ray->point.x, ray->vec.x,
			box->min.x, box->max.x, &t_min, &t_max}))
		return (false);
	if (!slab_hit((t_slab_args){ray->point.y, ray->vec.y,
			box->min.y, box->max.y, &t_min, &t_max}))
		return (false);
	return (slab_hit((t_slab_args){ray->point.z, ray->vec.z,
			box->min.z, box->max.z, &t_min, &t_max}));
}
