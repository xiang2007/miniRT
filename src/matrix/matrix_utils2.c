/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:56:03 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 09:36:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*transpose_matrix(t_matrix *m1)
{
	t_matrix	*res;
	int			i;
	int			j;

	if (!m1)
		return (NULL);
	res = create_matrix(m1->row, m1->col);
	if (!res)
		return (NULL);
	i = 0;
	while (i < m1->row)
	{
		j = 0;
		while (j < m1->col)
		{
			res->matrix[i][j] = m1->matrix[j][i];
			j++;
		}
		i++;
	}
	return (res);
}

int	determinant(t_matrix *m)
{
	int	res;
	int	i;
	t_d	**t;

	if (!m)
		return (-1);
	t = m->matrix;
	res = 0;
	if (m->col == 2 && m->row == 2)
		res = (t[0][0] * t[1][1]) - (t[0][1] * t[1][0]);
	else
	{
		i = 0;
		while (i < m->col)
		{
			res += t[0][i] * cofactor(m, 0, i);
			i++;
		}
	}
	return (res);
}

t_matrix	*dup_matrix(t_matrix *m)
{
	t_matrix	*t;
	int			i;
	int			j;

	if (!m)
		return (NULL);
	t = create_matrix(m->row, m->col);
	if (!t)
		return (NULL);
	i = 0;
	while (i < m->row)
	{
		j = 0;
		while (j < m->col)
		{
			t->matrix[i][j] = m->matrix[i][j];
			j++;
		}
		i++;
	}
	return (t);
}

int	minor_matrix(t_matrix *m, int row, int col)
{
	t_matrix	*t;
	t_matrix	*t1;
	int			d;

	if (!m)
		return (0);
	t = dup_matrix(m);
	t1 = sub_matrix(t, row, col);
	if (!t1)
		return (0);
	free_matrix(t);
	d = determinant(t1);
	free_matrix(t1);
	return (d);
}

t_matrix	*point_to_matrix(t_tuple *t)
{
	t_matrix	*m;

	if (!t)
		return (NULL);
	m = create_matrix(4, 1);
	if (!m)
		return (NULL);
	m->matrix[0][0] = t->x;
	m->matrix[1][0] = t->y;
	m->matrix[2][0] = t->z;
	m->matrix[3][0] = t->w;
	return (m);
}
