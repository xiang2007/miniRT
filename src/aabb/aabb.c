/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/20 07:10:14 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"

t_aabb surround_box(t_aabb a, t_aabb b)
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


t_aabb build_box(t_objects *o)
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