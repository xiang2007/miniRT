/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:11:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/14 22:20:08 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	*create_sub_matrix(t_matrix *m)
{
	t_matrix	*t;
	int			size;

	size = ((m->col + m->row) / 2) - 1;
	t = create_matrix(size, size);
	if (!t)
		return (NULL);
	return (t);
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
		j = 0;
		l = 0;
		if (k == row)
			k++;
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

t_matrix	*sub_matrix(t_matrix *m, int row, int col)
{
	t_matrix	*res;

	if (!m)
		return (NULL);
	if (row > m->row || col > m->col)
		return (NULL);
	res = create_sub_matrix(m);
	copy_valid(m, res, row, col);
	return (res);
}
