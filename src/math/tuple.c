/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 23:45:47 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 00:02:26 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*create_vector(t_d x, t_d y, t_d z)
{
	t_tuple	*tuple;

	tuple = malloc(sizeof(t_tuple));
	if (!tuple)
		return (NULL);
	tuple->x = x;
	tuple->y = y;
	tuple->z = x;
	tuple->flag = 0;
	return (tuple);
}

t_tuple	*create_point(t_d x, t_d y, t_d z)
{
	t_tuple	*tuple;

	tuple = malloc(sizeof(t_tuple));
	if (!tuple)
		return (NULL);
	tuple->x = x;
	tuple->y = y;
	tuple->z = x;
	tuple->flag = 1;
	return (tuple);
}

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*t;

	if (!t1 || !t2)
		return (NULL);
	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	if ((t1->flag + t2->flag) >= 1)
		t->flag == 1;
	else
		t->flag = 0;
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
	t->flag = abs(t1->flag - t2->flag);
	t->x = t1->x - t2->x;
	t->y = t1->y - t2->y;
	t->z = t1->z - t2->z;
	return (t);
}