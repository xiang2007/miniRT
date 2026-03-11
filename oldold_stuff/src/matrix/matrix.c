/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:07:59 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/04 19:56:16 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*create_matrix(int row, int col)
{
	t_matrix	*res;
	int			i;

	if (row < 1 || col < 1)
		return (NULL);
	i = 0;
	res = malloc(sizeof(t_matrix));
	if (!res)
		return (NULL);
	res->matrix = ft_calloc(row, sizeof(double *));
	if (!res->matrix)
		return (NULL);
	while (i < row)
	{
		res->matrix[i] = ft_calloc(col, sizeof(double));
		i++;
	}
	res->row = row;
	res->col = col;
	return (res);
}

void	set_mat_value(t_matrix *m, int val, int row, int col)
{
	if (!m)
		return ;
	if ((row >= m->row) || (col >= m->col))
		return ;
	m->matrix[row][col] = val;
}

void	print_mat(t_matrix *m)
{
	int	i;
	int	j;
	
	if (!m || !m->matrix)
		return ;
	printf("\n");
	i = 0;
	while (i < m->row)
	{
		j = 0;
		while (j < m->col)
		{
			printf("%4f ", m->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}	
}

void	free_matrix(t_matrix *m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < m->row)
	{
		free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	free(m);
}
