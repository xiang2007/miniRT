/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:50:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/16 08:56:22 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_ray()
{
	t_ray	*ray;
	t_tuple	*point;
	t_tuple	*vector;
	t_tuple	*res;

	point = create_point(2, 3, 4);
	vector = create_vector(1, 0, 0);
	ray = create_ray(point, vector);
	res = postition(ray, 1);
	print_tuple(res);
	free(point);
	free(vector);
	free_ray(ray);
	free(res);
}

void	transform_matrix(void)
{
	t_matrix	*m1;
	t_tuple		*t1;

	t1 = create_vector(-1, 1, 1);
	m1 = reflection(t1, 2, 3, 4);
	print_mat(m1);
	free(t1);
	free_matrix(m1);
}

void	rotate(t_mlx *m)
{
	t_tuple	*t1;
	t_tuple	*t2;
	int		cx;
	int		cy;
	int		r;
	int		x;
	int		y;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	r = 300;
	for (int i = 1; i <= 12; i++)
	{
		t1 = create_point(0, 0, 1);
		t2 = rot_y(t1, (i * PI / 6));
		x = cx + (int)(t2->x * r);
		y = cy - (int)(t2->z * r);
		mlx_put_pixel(m, x, y, 0xFFFFFF);
		free(t1);
		free(t2);
	}
}

void	set_matrix(void)
{
	t_matrix	*m1;
	// t_matrix	*m2;
	t_matrix	*m3;
	t_tuple		*t1;

	m1 = create_matrix(4, 4);
	m1->matrix[0][0] = 3;
	m1->matrix[0][1] = 5;
	m1->matrix[0][2] = 0;
	m1->matrix[0][3] = 2;
	m1->matrix[1][0] = 2;
	m1->matrix[1][1] = -1;
	m1->matrix[1][2] = -7;
	m1->matrix[1][3] = -1;
	m1->matrix[2][0] = 6;
	m1->matrix[2][1] = -1;
	m1->matrix[2][2] = 5;
	m1->matrix[2][3] = 6;
	m1->matrix[3][0] = -3;
	m1->matrix[3][1] = 0;
	m1->matrix[3][2] = -9;
	m1->matrix[3][3] = -4;
	
	// m2 = inverse_matrix(m1);
	t1 = create_vector(-3, 4, 5);
	m3 = mult_translation_vector(t1, 5, -3, 2);
	print_mat(m3);
	free(t1);
	free_matrix(m1);
	// free_matrix(m2);
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
	test_ray();
	return 0;
}
