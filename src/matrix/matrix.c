/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:28:11 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 09:38:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_matrix(int row, int col)
{
	t_matrix	*t;
	int			i;
	

	if (row < 0 || col < 0)
		return (NULL);
	t = malloc(sizeof(t_matrix));
	t->matrix = ft_calloc(row + 1, sizeof(t_d *));
	if (!t->matrix)
		return (NULL);
	i = 0;
	while (i < row)
	{
		t->matrix[i] = ft_calloc(col, sizeof(t_d));
		i++;
	}
	t->matrix[row] = NULL;
	t->col = col;
	t->row = row;
	return (t);
}

void	free_matrix(t_matrix *m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < m->row)
	{
		if (m->matrix[i])
			free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	m->col = 0;
	m->row = 0;
	free(m);
	return ;
}

int	compare_matrix(t_matrix *m1, t_matrix *m2)
{
	int	row;
	int	col;
	int	i;
	int	j;

	if (!m1 || !m2)
		return (-1);
	if ((m1->col != m2->col) || (m1->row != m2->row))
		return (0);
	row = m1->row;
	col = m1->col;
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			if (m1->matrix[i][j] != m2->matrix[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_matrix	*vector_to_matrix(t_tuple *t)
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
