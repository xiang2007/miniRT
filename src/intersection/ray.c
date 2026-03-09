/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:31:57 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/09 17:48:39 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_ray	*create_ray(t_tuple *point, t_tuple *dir)
{
	t_ray	*res;

	res = malloc(sizeof(t_ray));
	if (!res)
		return (NULL);
	res->point = tuple_dup(point);
	res->direction = tuple_dup(dir);
	free_temp_tuple(point);
	free_temp_tuple(dir);
	return (res);
}

void	free_ray(t_ray *r)
{
	if (!r)
		return ;
	free(r->direction);
	free(r->point);
	free(r);
}

