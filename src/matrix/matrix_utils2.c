/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:16:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/07 17:32:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	copy_valid(t_matrix *m, t_matrix *res, int row, int col);

t_matrix	*submatrix(t_matrix *m, int row, int col)
{
	t_matrix	*r;

	if (!m)
		return (NULL);
	r = create_matrix(m->row - 1, m->col - 1);
	if (!r)
		return (NULL);
	copy_valid(m, r, row, col);
	return (r);
}

static void	copy_valid(t_matrix *m, t_matrix *res, int row, int col)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	k = 0;
	while (i < res->row)
	{
		if (k == row)
			k++;
		j = 0;
		l = 0;
		while (j < res->col)
		{
			if (l == col)
				l++;
			res->matrix[i][j] = m->matrix[k][l];
			l++;
			j++;
		}
		k++;
		i++;
	}
}

double	matrix_minor(t_matrix *m, int row, int col)
{
	t_matrix	*mt;
	double		res;

	if (!m)
		return (-1);
	if ((row >= m->row) || (col >= m->col))
		return (-1);
	mt = submatrix(m, row, col);
	if (!mt)
		return (-1);
	res = matrix_determinant(mt);
	free_matrix(mt);
	return (res);
}

double	matrix_cofactor(t_matrix *mt, int row, int col)
{
	double		sign;
	double		res;

	sign = 1;
	if (!mt)
		return (-1);
	if ((row > mt->row) || (col > mt->col))
		return (-1);
	if ((row + col) % 2 != 0)
		sign = -1;
	res = matrix_minor(mt, row, col);
	return (res * sign);
}
