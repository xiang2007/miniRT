/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:50:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 00:56:33 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_matrix(void)
{
	t_matrix	*m1;
	t_matrix	*m2;
	t_matrix	*m3;
	t_tuple		*t1;
	// int	n;

	m1 = create_matrix(4, 4);
	m1->matrix[0][0] = 8;
	m1->matrix[0][1] = -5;
	m1->matrix[0][2] = 9;
	m1->matrix[0][3] = 2;
	m1->matrix[1][0] = 7;
	m1->matrix[1][1] = 5;
	m1->matrix[1][2] = 6;
	m1->matrix[1][3] = 1;
	m1->matrix[2][0] = -6;
	m1->matrix[2][1] = 0;
	m1->matrix[2][2] = 9;
	m1->matrix[2][3] = 6;
	m1->matrix[3][0] = -3;
	m1->matrix[3][1] = 0;
	m1->matrix[3][2] = -9;
	m1->matrix[3][3] = -4;
	
	print_mat(m1);
	// negate(m1);
	// n = determinant(m1);
	printf("\n");
	m2 = inverse_matrix(m1);
	t1 = create_point(-3, 4, 5);
	m3 = mult_inv_translate_matrix(t1, 5, -3, 2);
	print_mat(m3);
	free(t1);
	free_matrix(m1);
	free_matrix(m2);
	free_matrix(m3);
	return ;
}

int	main(void)
{
	// t_mlx	m;

	// init_mlx(&m);
	// mlx_put_to_window(&m);
	// mlx_hook(m.mlx_win, 17, 1L << 17, close_all, &m);
	// mlx_loop(m.mlx);
	set_matrix();
	return 0;
}
