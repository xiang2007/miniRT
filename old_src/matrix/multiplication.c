/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:27:33 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 11:07:55 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	col_mult(t_matrix *m , t_matrix *m1, t_matrix *m2, int row)
{
	int	col;
	int	k;

	col = 0;
	while (col < m2->col)
	{
		m->matrix[row][col] = 0;
		k = 0;
		while (k < m1->col)
		{
			m->matrix[row][col]
				+= m1->matrix[row][k] * m2->matrix[k][col];
			k++;
		}
		col++;
	}
}

t_matrix	*dynamic_mult_matrix(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*m;
	int			row;

	if (!m1 || !m2 || m1->col != m2->row)
		return (NULL);
	m = create_matrix(m1->row, m2->col);
	if (!m)
		return (NULL);
	row = 0;
	while (row < m1->row)
	{
		col_mult(m, m1, m2, row);
		row++;
	}
	return (m);
}

// 4x4 multiplication
t_matrix	*mult_matrix(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*m;
	int			row;
	int			col;

	if (!m1 || !m2)
		return (NULL);
	row = 0;
	m = create_matrix(4, 4);
	while (row < m->row)
	{
		col = 0;
		while (col < m->col)
		{
			m->matrix[row][col]
				= (m1->matrix[row][0] * m2->matrix[0][col]
					+ m1->matrix[row][1] * m2->matrix[1][col]
					+ m1->matrix[row][2] * m2->matrix[2][col]
					+ m1->matrix[row][3] * m2->matrix[3][col]);
			col++;
		}
		row++;
	}
	return (m);
}

t_matrix	*mult_free_s2(t_matrix *s1, t_matrix *s2)
{
	t_matrix	*res;

	if (!s1 || !s2)
		return (NULL);
	res = mult_matrix(s1, s2);
	free_matrix(s2);
	return (res);
}

t_matrix	*dy_mult_free_s2(t_matrix *s1, t_matrix *s2)
{
	t_matrix	*res;

	if (!s1 || !s2)
		return (NULL);
	res = dynamic_mult_matrix(s1, s2);
	free(s2);
	return (res);
}
