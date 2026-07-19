/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/18 11:24:23 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"

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