/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:18:17 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/07 16:53:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*res;

	if (!t1 || !t2)
		return (NULL);
	res = create_tuple((t1->x + t2->x), (t1->y + t2->y),
						(t1->z + t2->z), (t1->w + t2->w));
	if (!res)
		return (NULL);
	free_temp_tuple(t1);
	free_temp_tuple(t2);
	return (res);
}

t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*res;

	if (!t1 || !t2)
		return (NULL);
	res = create_tuple((t1->x - t2->x), (t1->y - t2->y),
						(t1->z - t2->z), fabs(t1->w - t2->w));
	if (!res)
		return (NULL);
	free_temp_tuple(t1);
	free_temp_tuple(t2);
	return (res);
}

t_tuple	*negate_tuple(t_tuple *t1)
{
	t_tuple	*res;

	if (!t1)
		return (NULL);
	res = create_tuple(-(t1->x), -(t1->y), -(t1->z), -(t1->w));
	if (!res)
		return (NULL);
	free_temp_tuple(t1);
	return (res);
}

void	print_tuple(t_tuple *t)
{
	if (!t)
		return ;
	printf("x:%f y:%f z:%f w:%f\n", t->x, t->y , t->z, t->w);
}

t_tuple	*tuple_dup(t_tuple *t)
{
	t_tuple	*res;

	if (!t)
		return (NULL);
	res = create_tuple(t->x, t->y, t->z, t->w);
	if (!res)
		return (NULL);
	return (res);
}
