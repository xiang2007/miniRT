/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:32:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:39:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_ray(t_ray *r)
{
	if (!r)
		return ;
	free(r->direction);
	free(r->origin);
	free(r);
}

t_ray	*create_ray(t_tuple *origin_point, t_tuple *direction_vector)
{
	t_ray	*res;

	res = malloc(sizeof(t_ray));
	if (!res)
		return (NULL);
	res->origin = create_point(origin_point->x, origin_point->y,
								origin_point->z);
	res->direction = create_vector(direction_vector->x, direction_vector->y,
									direction_vector->z);
	return (res);
}

t_tuple	*postition(t_ray *ray, t_d t)
{
	t_tuple	*scaled;
	t_tuple	*res;

	scaled = multiply_tuple(t, ray->direction);
	res = add_tuple(ray->origin, scaled);
	free(scaled);
	return (res);
}

void	print_ray(t_ray *r)
{
	if (!r)
		return ;
	printf("Origin: \n");
	print_tuple(r->origin);
	printf("Direction: \n");
	print_tuple(r->direction);
}
