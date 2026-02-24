/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:50:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:40:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_d	intersect(t_ray *ray, t_sp *sphere)
// {
// 	t_d	a;
// 	t_d	b;
// 	t_d	c;
// 	t_d	d;
// 	t_tuple	*str;

// 	(void)sphere;
// 	str = subtract_tuple(ray->origin, create_point(0, 0, 0));
// 	a = dot_product(ray->direction, ray->direction);
// 	b = 2 * (dot_product(ray->direction, str));
// 	c = dot_product(str, str) - 1;
// 	d = (sq(b)) - (4 * (a * c));
// 	if (d < 0)
// 		return (0);
// 	return (2);
// }

void	test_ray_transform()
{
	t_ray	*r;
	t_sp	*sp;
	t_sp	*temp;
	t_intersect	*t;

	r = create_ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	temp = create_sphere(create_point(0, 0, 0), 1);
	sp = transform_sphere(temp, translation(5, 0, 0));
	t = intersect(sp, r);
	print_intersect(t);
	free_ray(r);
	free(sp);
	free(t);
}

// void	*test_intersect()
// {
// 	t_sp	*sphere;
// 	t_intersect	*i1;
// 	t_intersect	*i2;
// 	t_intersect	*temp;

// 	sphere = create_sphere(0, 0, 0, 1);
// 	i1 = intersection(-1, sphere);
// 	i2 = intersection(1, sphere);
// 	add_intersect(i2, &i1);
// 	temp = hit(i1);
// 	printf("i1: %f i2: %f temp: %f\n", i1->t, i2->t, temp->t);
// 	return (NULL);
// }

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
	// test_ray();
	test_ray_transform();
	return 0;
}
