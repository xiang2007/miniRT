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
	int	n;

	if (!t1)
		return (-1);
	if (t1->w != 0)
		return (-1);
	n = sqrt(sq(t1->x) + sq(t1->y)
	+ sq(t1->z) + sq(t1->w));
	return (n);
}

void	*normalize(t_tuple *t1)
{
	t_d	m;

	if (!t1)
		return (NULL);
	m = magnitude(t1);
	if (m == -1)
		return (NULL);
	t1->w / m;
	t1->x / m;
	t1->y / m;
	t1->z / m;
}

t_d	dot_product(t_tuple *t1, t_tuple *t2)
{
	if (!t1 || !t2)
		return (-1);
	
}