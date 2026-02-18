/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:52:27 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 23:19:30 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_identity_matrix(t_matrix *identity)
{
	int	i;
	int	j;

	if (!identity || identity->row != 4 || identity->col != 4)
		return ;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				identity->matrix[i][j] = 1;
			else
				identity->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	identity_matrix(t_matrix **m)
{
	t_matrix	*identity;
	t_matrix	*res;

	if (!m || (*m)->row != 4 || (*m)->col != 4)
		return ;
	identity = create_matrix(4, 4);
	if (!identity)
		return ;
	set_identity_matrix(identity);
	res = mult_matrix(*m, identity);
	free_matrix(identity);
	free_matrix(*m);
	*m = res;
}

t_matrix	*mult_matrix_w_tuple(t_matrix *m1, t_tuple *t)
{
	t_matrix	*m;
	t_matrix	*res;

	if (!m1 || !t)
		return (NULL);
	m = create_matrix(4, 1);
	if (!m)
		return (NULL);
	m->matrix[0][0] = t->x;
	m->matrix[1][0] = t->y;
	m->matrix[2][0] = t->z;
	m->matrix[3][0] = t->w;
	res = mult_matrix(m1, m);
	free_matrix(m);
	return (res);
}
/// @brief Allocate new matrix and content will be the multiply of m1 and m2
/// @param m1 
/// @param m2 
/// @return Malloced matrix
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

void	print_mat(t_matrix *m)
{
	int	i;
	int	j;
	
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
