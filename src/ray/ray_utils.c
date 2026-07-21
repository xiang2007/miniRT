/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 19:34:26 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/vec3.h"

double	get_ray_vec_n(t_ray *ray, int n)
{
	double res;

	res = 0;
	if(!ray)
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
	double res;

	res = 0;
	if(!ray)
		return (-1);
	if (n == 1)
		res = ray->point.x;
	else if (n == 2)
		res = ray->point.y;
	else
		res = ray->point.z;
	return (res);
}