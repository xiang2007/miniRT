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

double	get_ray_vec_n(t_ray *ray, int n)
{
	double	res;

	res = 0;
	if (!ray)
		return (-1);
	if (n == 1)
		res = ray->vec.x;
	else if (n == 2)
		res = ray->vec.y;
	else
		res = ray->vec.z;
	return (res);
}

double	get_ray_point_n(t_ray *ray, int n)
{
	double	res;

	res = 0;
	if (!ray)
		return (-1);
	if (n == 1)
		res = ray->point.x;
	else if (n == 2)
		res = ray->point.y;
	else
		res = ray->point.z;
	return (res);
}

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

	scaled_dir = vec_mul(r->vec, t);
	res = vec_add(r->point, scaled_dir);
	return (res);
}
