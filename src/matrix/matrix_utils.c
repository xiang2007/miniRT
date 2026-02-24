/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:52:27 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:10:39 by wshou-xi         ###   ########.fr       */
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

t_matrix	*create_transformation_matrix(void)
{
	t_matrix	*res;

	res = create_matrix(4, 4);
	set_identity_matrix(res);
	return (res);
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
