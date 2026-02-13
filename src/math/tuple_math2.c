	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:59:23 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 07:13:44 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_d	sq(t_d n)
{
	return (n * n);
}

t_d	magnitude(t_tuple *t1)
{
	t_d	n;

	if (!t1)
		return (-1);
	if (t1->w != 0)
		return (-1);
	n = sqrt(sq(t1->x) + sq(t1->y)
	+ sq(t1->z) + sq(t1->w));
	return (n);
}

t_tuple	*normalize(t_tuple *t1)
{
	t_d	m;
	t_tuple	*t;

	if (!t1)
		return (NULL);
	m = magnitude(t1);
	if (m == -1)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->w = t1->w / m;
	t->x = t1-> x / m;
	t->y = t1-> y / m;
	t->z = t1-> z / m;
	return (t);
}

t_d	dot_product(t_tuple *t1, t_tuple *t2)
{
	if (!t1 || !t2)
		return (-1);
	return ((t1->x * t2->x) + (t1->y * t2->y)
		+ (t1->z * t2->z) + (t1->w + t2->w));
}

t_tuple	*cross(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*t;

	if (!t1 || !t2)
		return (NULL);
	if (t1->w == 1 || t2->w == 1)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = (t1->y * t2->z) - (t1->z * t2->y);
	t->y = (t1->z * t2->x) - (t1->x * t2->z);
	t->z = (t1->x * t2->y) - (t1->y * t2->x);
	return (t);
}
