/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:55:22 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/04 14:49:47 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*multiple_tuple_scalar(double scalar, t_tuple *t)
{
	t_tuple	*res;

	if (!t)
		return (NULL);
	res = malloc(sizeof(t_tuple));
	res->x = t->x * scalar;
	res->y = t->y * scalar;
	res->z = t->z * scalar;
	res->w = t->w * scalar;
	res->free = 0;
	free_temp_tuple(t);
	return (res);
}

t_tuple	*divide_tuple_scalar(double scalar, t_tuple *t)
{
	t_tuple	*res;

	if (!t)
		return (NULL);
	res = malloc(sizeof(t_tuple));
	res->x = t->x * scalar;
	res->y = t->y * scalar;
	res->z = t->z * scalar;
	res->w = t->w * scalar;
	res->free = 0;
	free_temp_tuple(t);
	return (res);
}
