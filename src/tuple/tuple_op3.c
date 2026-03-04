/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_op3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:50 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/04 18:04:57 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	magnitde(t_tuple *t)
{
	double	res;

	if (!t)
		return (0);
	res = sqrt((sq(t->x)) + (sq(t->y)) + (sq(t->z)) + (sq(t->w)));
	free_temp_tuple(t);
	return (res);
}

t_tuple	*tuple_normalize(t_tuple *t)
{
	t_tuple	*res;
	double	m;

	if (!t)
		return (NULL);
	m = magnitde(t);
	res = create_tuple(((t->x) / m), ((t->y) / m), ((t->z) / m), ((t->w) / m));
	free_temp_tuple(t);
	return (res);
}

double	dot_product(t_tuple *t1, t_tuple *t2)
{
	double	res;

	if (!t1 || !t2)
		return (0);
	res = ((t1->x * t2->x) + (t1->y * t2->y) + (t1->z * t2->z)
			+ (t1->w * t2->w));
	free_temp_tuple(t1);
	free_temp_tuple(t2);
	return (res);
}

t_tuple	*mult_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*res;

	if (!t1 || !t2)
		return (NULL);
	res = create_tuple((t1->x * t2->x), (t1->y * t2->y), (t1->z * t2->z),
						(t1->w * t2->w));
	if (!res)
		return (NULL);
	free_temp_tuple(t1);
	free_temp_tuple(t2);
	return (res); 
}
// Cross product of 2 vector
t_tuple	*tuple_cross(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*res;

	if (!t1 || !t2)
		return (NULL);
	if ((t1->w == 1) || (t2->w == 1))
		return (NULL);
	res = create_vector(((t1->y * t2->z) - (t1->z * t2->y)),
						((t1->z * t2->x) - (t1->x * t2->z)),
						((t1->x * t2->y) - (t1->y * t2->x)));
	if (!res)
		return (NULL);
	free_temp_tuple(t1);
	free_temp_tuple(t2);
	return (res);
}
