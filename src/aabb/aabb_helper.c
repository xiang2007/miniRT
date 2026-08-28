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
#include "../../includes/ray.h"

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