/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:17:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"
#include "../../includes/ray.h"

void	build_cylinder(t_aabb *box, t_objects *o, t_vec3 half_axis, t_aabbs e)
{
	if (vec_len_sq(o->cylinder.axis) > 0.0)
		half_axis = vec_mul(unit_vec(o->cylinder.axis),
				o->cylinder.height / 2.0);
	else
		half_axis = create_vec3(0, 0, 0);
	e.e1 = vec_add(o->cylinder.center, half_axis);
	e.e2 = vec_sub(o->cylinder.center, half_axis);
	box->min = create_vec3(fmin(e.e1.x, e.e2.x) - o->cylinder.radius,
			fmin(e.e1.y, e.e2.y) - o->cylinder.radius,
			fmin(e.e1.z, e.e2.z) - o->cylinder.radius);
	box->max = create_vec3(fmax(e.e1.x, e.e2.x) + o->cylinder.radius,
			fmax(e.e1.y, e.e2.y) + o->cylinder.radius,
			fmax(e.e1.z, e.e2.z) + o->cylinder.radius);
}

t_aabb	build_box(t_objects *o)
{
	t_aabbs	t;

	t.box.max = create_vec3(0, 0, 0);
	t.box.min = create_vec3(0, 0, 0);
	if (o->type == OBJ_SPHERE)
	{
		t.box.min = create_vec3(o->sphere.point.x - o->sphere.radius,
				o->sphere.point.y - o->sphere.radius,
				o->sphere.point.z - o->sphere.radius);
		t.box.max = create_vec3(o->sphere.point.x + o->sphere.radius,
				o->sphere.point.y + o->sphere.radius,
				o->sphere.point.z + o->sphere.radius);
	}
	else if (o->type == OBJ_CYLINDER)
		build_cylinder(&t.box, o, t.half_axis, t);
	else if (o->type == OBJ_CONE)
		build_cone(&t.box, &o->cone);
	return (t.box);
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
