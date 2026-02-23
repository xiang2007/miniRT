/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:55:01 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/20 12:33:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_invertible(t_matrix *m)
{
	int	n;

	if (!m)
		return (0);
	n = determinant(m);
	if (n == 0)
		return (0);
	return (1);
}

t_matrix	*inverse_matrix(t_matrix *m)
{
	t_matrix	*t;
	int			i;
	int			j;
	t_d			det;

	if (is_invertible(m) == 0)
		return (NULL);
	t = create_matrix(m->row, m->col);
	det = (t_d)determinant(m);
	i = 0;
	while (i < m->row)
	{
		j = 0;
		while (j < m->col)
		{
			t->matrix[j][i] = (t_d)cofactor(m, i, j) / det;
			j++;
		}
		i++;
	}
	return (t);
}

t_matrix	*inv_and_free(t_matrix *m)
{
	t_matrix	*res;

	if (!m)
		return (NULL);
	res = inverse_matrix(m);
	free(m);
	return (res);
}
