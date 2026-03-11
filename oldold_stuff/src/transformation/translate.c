/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:28:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/08 12:55:40 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	*matrix_translation_inv_mat(double x, double y, double z)
{
	t_matrix	*m;
	t_matrix	*res;
	double		**mt;

	m = create_identity_matrix();
	mt = m->matrix;
	mt[0][3] = (x);
	mt[1][3] = (y);
	mt[2][3] = (z);
	res = matrix_inverse(m);
	print_mat(res);
	free_matrix(m);
	return (res);
}

static t_matrix	*matrix_translation_mat(double x, double y, double z)
{
	t_matrix	*m;
	double		**mt;

	m = create_identity_matrix();
	if (!m)
		return (NULL);
	mt = m->matrix;
	mt[0][3] = (x);
	mt[1][3] = (y);
	mt[2][3] = (z);
	return (m);
}

t_tuple	* matrix_translation(t_tuple *p, double x, double y, double z)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (free_temp_tuple(p), NULL);
	m = matrix_translation_mat(x, y, z);
	if (!m)
		return (free_temp_tuple(p), NULL);
	res = mult_tuple_matrix(p, m);
	free_matrix(m);
	if (!res)
		return (free_temp_tuple(p), NULL);
	return (res);
}

t_tuple	*matrix_translation_inv(t_tuple *p, double x, double y, double z)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (free_temp_tuple(p), NULL);
	m = matrix_translation_inv_mat(x, y, z);
	if (!m)
		return (free_temp_tuple(p), NULL);
	res = mult_tuple_matrix(p, m);
	free_matrix(m);
	if (!res)
		return (free_temp_tuple(p), NULL);
	return (res);
}
