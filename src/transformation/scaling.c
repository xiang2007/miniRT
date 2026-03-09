/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 11:51:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/08 15:43:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	*matrix_scaling_inv_calc(double x, double y, double z)
{
	t_matrix	*m;
	t_matrix	*inv;
	double		**mt;

	m = create_identity_matrix();
	if (!m)
		return (NULL);
	mt = m->matrix;
	mt[0][0] = x;
	mt[1][1] = y;
	mt[2][2] = z;
	print_mat(m);
	inv = matrix_inverse(m);
	print_mat(inv);
	free_matrix(m);
	return (inv);
}

static t_matrix	*matrix_scaling_calc(double x, double y, double z)
{
	t_matrix	*m;
	double		**mt;

	m = create_identity_matrix();
	if (!m)
		return (NULL);
	mt = m->matrix;
	mt[0][0] = x;
	mt[1][1] = y;
	mt[2][2] = z;
	return (m);
}

t_tuple	*matrix_scaling(t_tuple *p, double x, double y, double z)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (NULL);
	m = matrix_scaling_calc(x, y, z);
	if (!m)
		return (free_temp_tuple(p), NULL);
	res = mult_tuple_matrix(p, m);
	if (!res)
		return (free_temp_tuple(p), NULL);
	free_matrix(m);
	return (res);
}

t_tuple	*matrix_scaling_inv(t_tuple *p, double x, double y, double z)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (NULL);
	m = matrix_scaling_inv_calc(x, y, z);
	if (!m)
		return (free_temp_tuple(p), NULL);
	res = mult_tuple_matrix(p, m);
	if (!res)
		return (free_temp_tuple(p), NULL);
	free_matrix(m);
	return (res);
}

t_tuple	*matrix_reflection(t_tuple *t)
{
	t_tuple		*res;

	if (!t)
		return (NULL);
	res = matrix_scaling(t, -1, 1, 1); 
	return (res);
}
