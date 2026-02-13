/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:50:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/14 00:50:57 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_mat(t_matrix *m)
{
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < m->col; j++)
			printf("%4d", m->matrix[i][j]);
		printf("\n");
	}
}

void	set_matrix(void)
{
	t_matrix	*m1;
	t_matrix	*m2;

	m1 = create_matrix(4, 4);
	m2 = create_matrix(4, 4);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m1->matrix[i][j] = i * 4 + j + 1;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m2->matrix[i][j] = i * 4 + j + 2;

	int flag = compare_matrix(m1, m2);
	printf("Flag is %d\n\n", flag);
	print_mat(m1);
	printf("\n");
	print_mat(m2);
	free_matrix(m1);
	free_matrix(m2);
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
