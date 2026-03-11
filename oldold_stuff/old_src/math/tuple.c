/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 23:45:47 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 13:19:38 by wshou-xi         ###   ########.fr       */
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
	tuple->z = z;
	tuple->w = 0;
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
	tuple->z = z;
	tuple->w = 1;
	return (tuple);
}

t_tuple	*create_tuple_w(t_tuple *t1)
{
	if (!t1)
		return (NULL);
	if (t1->w == 1)
		return (create_point(0, 0, 0));
	else if (t1->w == 0)
		return (create_vector(0, 0, 0));
	else
		return (NULL);
}
