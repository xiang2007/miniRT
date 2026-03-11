/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:38:07 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/07 17:32:08 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	matrix_determinant(t_matrix *m)
{
	int	size;
	int	i;
	double	res;
	
	if (!m)
		return (-1);
	size = (m->col + m->row) / 2;
	res = 0;
	if (size == 2)
	{
		res = (m->matrix[0][0] * m->matrix[1][1])
			- (m->matrix[0][1] * m->matrix[1][0]);
	}
	else
	{
		i = 0;
		while (i < size)
		{
			res += (double)(m->matrix[0][i] * matrix_cofactor(m, 0, i));
			i++;
		}
	}
	return (res);
}

int	invertible(t_matrix *m)
{
	int	res;

	res = matrix_determinant(m);
	if (res == 0)
		return (0);
	return (1);
}

static void	matrix_inverse_calculation(t_matrix *m, t_matrix *r, double det)
{
	int		i;
	int		j;
	double	**d;
	double	cof;

	if (!m)
		return ;
	d = r->matrix;
	i = 0;
	while (i < m->row)
	{
		j = 0;
		while (j < m->col)
		{
			cof = matrix_cofactor(m, i, j);
			d[j][i] = (cof / det);
			j++;
		}
		i++;
	}
}

t_matrix	*matrix_inverse(t_matrix *m)
{
	int			size;
	double		det;
	t_matrix	*r;

	if (!m)
		return (NULL);
	if (invertible(m) == 0)
		return (NULL);
	size = (m->row + m->col) / 2;
	r = create_matrix(size, size);
	if (!r)
		return (NULL);
	det = matrix_determinant(m);
	matrix_inverse_calculation(m, r, det);
	return (r);
}
