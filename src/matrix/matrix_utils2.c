/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:16:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/05 00:32:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	copy_valid(t_matrix *m, t_matrix *res, int row, int col);

double	determinant(t_matrix *m)
{
	double	res;
	double	**r;

	if (!m)
		return (-1);
	r = m->matrix;
	res = (r[0][0] * r[1][1]) - (r[0][1] * r[1][0]);
	return (res);
}

t_matrix	*submatrix(t_matrix *m, int row, int col)
{
	t_matrix	*r;
	int			size;

	if (!m)
		return (NULL);
	size = ((m->row + m->col) / 2) -1;
	r = create_matrix(size, size);
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
