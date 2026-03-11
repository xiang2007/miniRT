/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:50:23 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 23:03:48 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*translate_ray(t_ray *r, double x, double y, double z)
{
	t_ray	*res;
	t_tuple	*new_point;
	t_tuple	*new_dir;

	if (!r)
		return (NULL);
	new_point = matrix_translation(r->point, x, y, z);
	new_dir = matrix_translation(r->direction,x, y, z);
	res = create_ray(new_point, new_dir);
	free(new_point);
	free(new_dir);
	return (res);
}

t_ray	*scale_ray(t_ray *r, double x, double y, double z)
{
	t_ray	*res;
	t_tuple	*new_point;
	t_tuple	*new_dir;

	if (!r)
		return (NULL);
	new_point = matrix_scaling(r->point, x, y, z);
	new_dir = matrix_scaling(r->direction,x, y, z);
	res = create_ray(new_point, new_dir);
	free(new_point);
	free(new_dir);
	return (res);
}
