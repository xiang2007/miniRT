/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 18:57:32 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"

/**
 * @brief Calculates the ray position in terms of distance (t)
 * Hit Point = Origin + (t * Direction)
 *
 * @param r the ray
 * @param t the distance
 * @return the position of the ray at 't' distance
 */
t_vec3	ray_pos(t_ray *r, double t)
{
	t_vec3		scaled_dir;
	t_point3	res;

	scaled_dir = vec3_mul(r->vec, t);
	res = vec3_add(r->point, scaled_dir);
	return (res);
}
