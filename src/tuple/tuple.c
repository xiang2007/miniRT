/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:05:34 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/03 18:52:09 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*create_temp_tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (&tuple);
}

t_tuple	*create_tuple(double x, double y, double z, double w)
{
	t_tuple	*res;

	res = malloc(sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = x;
	res->y = y;
	res->z = z;
	res->w = w;
	return (res);
}

t_tuple	*create_point(double x, double y, double z)
{
	t_tuple	*res;

	res = create_tuple(x, y, z, 1);
	if (!res)
		return (NULL);
	return (res);
}

t_tuple	*create_vector(double x, double y, double z)
{
	t_tuple	*res;

	res = create_tuple(x, y, z, 0);
	if (!res)
		return (NULL);
	return (res);
}
