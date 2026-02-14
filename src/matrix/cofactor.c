/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:00:50 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 01:05:17 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	negate(t_matrix *m)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 1;
	while (i < m->row)
	{
		j = 0;
		while (j < m->col)
		{
			m->matrix[i][j] *= flag;
			flag *= -1;
			j++;
		}
		i++;
	}
}

int	cofactor(t_matrix *m1, int row, int col)
{
	t_matrix	*temp;
	t_d			minor;
	int			n;

	if (!m1 || row > m1->row || col > m1->col)
		return (0);
	temp = sub_matrix(m1, row, col);
	if (!temp)
		return (0);
	minor = determinant(temp);
	free_matrix(temp);
	if ((row + col) % 2 == 0)
		n = 1;
	else
		n = 0;
	return (n * minor);
}
