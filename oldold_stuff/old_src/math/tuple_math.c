/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:44:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 15:52:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*t;

	if (!t1 || !t2)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	if ((t1->w + t2->w) >= 1)
		t->w = 1;
	else
		t->w = 0;
	t->x = t1->x + t2->x;
	t->y = t1->y + t2->y;
	t->z = t1->z + t2->z;
	return (t);
}

t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*t;

	if (!t1 || !t2)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->w = fabs(t1->w - t2->w);
	t->x = t1->x - t2->x;
	t->y = t1->y - t2->y;
	t->z = t1->z - t2->z;
	return (t);
}

t_tuple	*neg_tuple(t_tuple *t1)
{
	t_tuple	*t;

	if (!t1)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->w = -t1->w;
	t->x = -t1->x;
	t->y = -t1->y;
	t->z = -t1->z;
	return (t);
}

t_tuple	*multiply_tuple(t_d n, t_tuple *t1)
{
	t_tuple	*t;

	if (!t1)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->w = t1->w * n;
	t->x = t1->x * n;
	t->y = t1->y * n;
	t->z = t1->z * n;
	return (t);
}

t_tuple	*divide_tuple(t_d n, t_tuple *t1)
{
	t_tuple	*t;

	if (!t1)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->w = t1->w / n;
	t->x = t1->x / n;
	t->y = t1->y / n;
	t->z = t1->z / n;
	return (t);
}
