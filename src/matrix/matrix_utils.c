/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:59:40 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/05 00:12:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_matrix(t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (!m1 || !m2)
		return (0);
	if ((m1->col != m2->col) || (m1->row != m2->row))
		return (0);
	i = 0;
	while (i < m1->row)
	{
		j = 0;
		while (j < m1->col)
		{
			if (m1->matrix[i][j] != m2->matrix[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_matrix	*multiply_matrix(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*res;
	int			row;
	int			col;

	if (!m1 || !m2)
		return (NULL);
	if ((m1->row != m2->row) || (m1->col != m2->col))
		return (NULL);
	res = create_matrix(m1->row, m1->col);
	row = 0;
	while (row <= 3)
	{
		col = 0;
		while (col <= 3)
		{
			res->matrix[row][col] = (m1->matrix[row][0] * m2->matrix[0][col]
									+ m1->matrix[row][1] * m2->matrix[1][col]
									+ m1->matrix[row][2] * m2->matrix[2][col]
									+ m1->matrix[row][3] * m2->matrix[3][col]);
			col++;
		}
		row++;
	}
	return (res);
}

t_tuple	*mult_tuple_matrix(t_tuple *t, t_matrix *mt)
{
	t_tuple	*res;
	double	**m;

	if (!t || !mt)
		return (NULL);
	m = mt->matrix;
	res = create_tuple(0, 0, 0, 0);
	res->x = (m[0][0] * t->x) + (m[0][1] * t->y) + (m[0][2] * t->z)
			+ (m[0][3] * t->w);
	res->y = (m[1][0] * t->x) + (m[1][1] * t->y) + (m[1][2] * t->z)
			+ (m[1][3] * t->w);
	res->z = (m[2][0] * t->x) + (m[2][1] * t->y) + (m[2][2] * t->z)
			+ (m[2][3] * t->w);
	res->w = (m[3][0] * t->x) + (m[3][1] * t->y) + (m[3][2] * t->z)
			+ (m[3][3] * t->w);
	free_temp_tuple(t);
	return (res);
}

t_matrix	*create_identity_matrix()
{
	t_matrix	*m;
	double		**d;

	m = create_matrix(4, 4);
	if (!m)
		return (NULL);
	d = m->matrix;
	d[0][0] = 1;
	d[1][1] = 1;
	d[2][2] = 1;
	d[3][3] = 1;
	return (m);
}

t_matrix	*transpose_matrix(t_matrix *m)
{
	t_matrix	*r;
	int			row;
	int			col;
	
	if (!m)
		return (NULL);
	r = create_matrix(m->row, m->col);
	if (!r)
		return (NULL);
	row = 0;
	while (row < m->row)
	{
		col = 0;
		while (col < m->col)
		{
			r->matrix[col][row] = m->matrix[row][col];
			col++;
		}
		row++;
	}
	return (r);
}
