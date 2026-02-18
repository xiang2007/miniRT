/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 10:04:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 11:50:40 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*scaling(int x, int y, int z)
{
	t_matrix	*m1;
	t_d			**m;

	m1 = create_matrix(4, 4);
	if (!m1)
		return (NULL);
	m = m1->matrix;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = 1;
	return (m1);
}

t_matrix	*scale_to_point(t_tuple *p, int x, int y, int z)
{
	t_matrix	*m1;
	t_matrix	*point;
	t_matrix	*res;

	if (!p)
		return (NULL);
	m1 = scaling(x, y, z);
	if (!m1)
		return (NULL);
	point = point_to_matrix(p);
	if (!point)
		return (free_matrix(m1), NULL);
	res = dynamic_mult_matrix(m1, point);
	free_matrix(m1);
	free_matrix(point);
	return (res);
}

t_matrix	*scale_to_vec(t_tuple *v, int x, int y, int z)
{
	t_matrix	*scale;
	t_matrix	*vector;
	t_matrix	*res;

	if (!v)
		return (NULL);
	scale = scaling(x, y, z);
	if (!scale)
		return (NULL);
	vector = point_to_matrix(v);
	if (!vector)
		return (free_matrix(scale), NULL);
	res = dynamic_mult_matrix(scale, vector);
	free_matrix(scale);
	free_matrix(vector);
	return (res);
}

t_matrix	*inv_scale_to_vec(t_tuple *v, int x, int y, int z)
{
	t_matrix	*scale;
	t_matrix	*inv;
	t_matrix	*vm;
	t_matrix	*res;

	if (!v)
		return (NULL);
	scale = scaling(x, y, z);
	if (!scale)
		return (NULL);
	inv = inverse_matrix(scale);
	if (!inv)
		return (free_matrix(scale), NULL);
	vm = vector_to_matrix(v);
	if (!vm)
		return (free_matrix(scale), free_matrix(inv), NULL);
	res = dynamic_mult_matrix(inv, vm);
	if (!res)
		return (free_matrix(scale), free_matrix(inv), free_matrix(vm), NULL);
	free_matrix(scale);
	free_matrix(inv);
	free_matrix(vm);
	return (res);
}

t_matrix	*reflection(t_tuple *p, int x, int y, int z)
{
	t_matrix	*scale;
	t_matrix	*point;
	t_matrix	*res;

	if (!p)
		return (NULL);
	scale = scaling(x, y, z);
	if (!scale)
		return (NULL);
	point = point_to_matrix(p);
	if (!point)
		return (free_matrix(scale), point);
	res = dynamic_mult_matrix(scale, point);
	if (!res)
		return (free_matrix(scale), free_matrix(point), NULL);
	free_matrix(scale);
	free_matrix(point);
	return (res);
}
