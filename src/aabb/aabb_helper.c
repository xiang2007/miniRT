/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:50:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/28 16:33:07 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aabb.h"

void	build_cone(t_aabb *box, t_cone *cone)
{
	t_vec3	base;
	t_vec3	extent;

	base = vec_add(cone->pos, vec_mul(cone->axis, cone->height));
	extent.x = cone->radius * sqrt(fmax(0.0,
				1.0 - cone->axis.x * cone->axis.x));
	extent.y = cone->radius * sqrt(fmax(0.0,
				1.0 - cone->axis.y * cone->axis.y));
	extent.z = cone->radius * sqrt(fmax(0.0,
				1.0 - cone->axis.z * cone->axis.z));
	box->min = create_vec3(fmin(cone->pos.x, base.x - extent.x),
			fmin(cone->pos.y, base.y - extent.y),
			fmin(cone->pos.z, base.z - extent.z));
	box->max = create_vec3(fmax(cone->pos.x, base.x + extent.x),
			fmax(cone->pos.y, base.y + extent.y),
			fmax(cone->pos.z, base.z + extent.z));
}

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
