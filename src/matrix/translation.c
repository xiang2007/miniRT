/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:31:12 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 00:57:34 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*translation(int x, int y, int z)
{
	t_matrix	*t;

	t = create_matrix(4, 4);
	if (!t)
		return (NULL);
	set_identity_matrix(t);
	t->matrix[0][3] = x;
	t->matrix[1][3] = y;
	t->matrix[2][3] = z;
	return (t);
}

t_matrix	*mult_translate_matrix(t_tuple *point, int x, int y, int z)
{
	t_matrix	*m;
	t_matrix	*m2;
	t_matrix	*tuple;

	m = translation(x, y, z);
	tuple = tuple_to_matrix(point);
	m2 = dynamic_mult_matrix(m, tuple);
	if (!m2)
	{
		free_matrix(tuple);
		free_matrix(m);
		return (NULL);
	}
	free_matrix(tuple);
	free_matrix(m);
	return (m2);
}

t_matrix	*mult_inv_translate_matrix(t_tuple *point, int x, int y, int z)
{
	t_matrix	*m;
	t_matrix	*m2;
	t_matrix	*inv;
	t_matrix	*tuple;

	m = translation(x, y, z);
	inv = inverse_matrix(m);
	print_mat(inv);
	tuple = tuple_to_matrix(point);
	m2 = dynamic_mult_matrix(inv, tuple);
	if (!m2)
	{
		free_matrix(tuple);
		free_matrix(m);
		free_matrix(inv);
		return (NULL);
	}
	free_matrix(m);
	free_matrix(inv);
	free_matrix(tuple);
	return(m2);
}
