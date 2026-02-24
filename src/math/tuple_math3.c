/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:06:14 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 13:15:16 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*mult_2_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*res;

	if (!t1 || !t2)
		return (NULL);
	res = create_point((t1->x * t2->x), (t1->y * t2->y),
						(t1->z * t2->z));
	if (!res)
		return (NULL);
	return (res);
}

void	print_tuple(t_tuple *t)
{
	printf("%4f\n", t->x);
	printf("%4f\n", t->y);
	printf("%4f\n\n", t->z);
}

t_tuple	*sub_free_s2(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*temp;

	temp = subtract_tuple(t1, t2);
	free(t2);
	return (temp);
}

t_tuple	*dup_tuple(t_tuple *t)
{
	t_tuple	*res;

	if (!t)
		return (NULL);
	res = NULL;
	if (t->w == 1)
		res = create_point(t->x, t->y, t->z);
	else if (t->w == 0)
		res = create_vector(t->x, t->y, t->z);
	if (!res)
		return (NULL);
	return (res);
}
