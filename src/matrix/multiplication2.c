/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:08:44 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:39:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*mult_matrix_w_tuple(t_matrix *m1, t_tuple *t)
{
	t_matrix	*m;
	t_matrix	*res;

	if (!m1 || !t)
		return (NULL);
	m = create_matrix(4, 1);
	if (!m)
		return (NULL);
	m->matrix[0][0] = t->x;
	m->matrix[1][0] = t->y;
	m->matrix[2][0] = t->z;
	m->matrix[3][0] = t->w;
	res = mult_matrix(m1, m);
	free_matrix(m);
	return (res);
}

t_d	m_multi(t_matrix *m, t_tuple *t, int row, int col)
{
	(void)col;
	if (!m || !t || row < 0 || row >= 4)
		return (0);
	return ((m->matrix[row][0] * t->x)
			+ (m->matrix[row][1] * t->y)
			+ (m->matrix[row][2] * t->z)
			+ (m->matrix[row][3] * t->w));
}

t_tuple	*mult_matrix_tuple(t_matrix *m1, t_tuple *t1)
{
	t_tuple	*res;

	if (!m1 || !t1 || m1->row < 4 || m1->col < 4)
		return (NULL);
	res = create_tuple_w(t1);
	if (!res)
		return (NULL);
	res->x = m_multi(m1, t1, 0, 0);
	res->y = m_multi(m1, t1, 1, 0);
	res->z = m_multi(m1, t1, 2, 0);
	res->w = m_multi(m1, t1, 3, 0);
	return (res);
}
