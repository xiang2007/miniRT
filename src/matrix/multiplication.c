/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:27:33 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 00:46:29 by wshou-xi         ###   ########.fr       */
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