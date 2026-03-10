/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:08 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 23:04:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_ray	*ori;
	t_ray	*new;

	ori = create_ray(create_temp_tuple(1, 2, 3, 1), create_temp_tuple(0, 1, 0, 0));
	new = scale_ray(ori, 2, 3, 4);
	print_tuple(new->direction);
	print_tuple(new->point);
	free_ray(ori);
	free_ray(new);
}

// t_intersect	*intersect_loop()
// {
// 	t_intersect	*head;
// 	int			i = 0;

// 	head = intersect(create_ray(create_temp_tuple(0, 0, i, 1),
// 			create_temp_tuple(0, 0, 1, 0)), create_sphere(1));
// 	while (i < 20)
// 	{
// 		add_intersect_back(intersect(create_ray(create_temp_tuple(0, 0, -i - 1, 1),
// 			create_temp_tuple(0, 0, 1, 0)), create_sphere(i + 2)), &head);
// 		i++;
// 	}
// 	return (head);
// }

// int	main()
// {
// 	t_intersect	*head;
// 	t_intersect	*pointer;

// 	head = intersect_loop();
// 	pointer = head;
// 	while (pointer)
// 	{
// 		print_intersect(pointer);
// 		pointer = pointer->next;
// 	}
// 	free_intersect_list(head);
// }

// int	main()
// {
// 	t_ray	*res;
// 	t_ray	*res1;
// 	t_intersect	*i2;
// 	t_intersect	*i;
// 	t_sphere	*sp;

// 	res = create_ray(create_temp_tuple(0, 0, 1, 1), create_temp_tuple(0, 0, 1, 0));
// 	res1 = create_ray(create_temp_tuple(0, 0, 2, 1), create_temp_tuple(0, 0, 1, 0));
// 	sp = create_sphere();
// 	i = intersect(res, sp);
// 	i2 = intersect(res1, sp);
// 	add_intersect_back(i2, &i);
// 	print_intersect(i);
// 	print_intersect(i->next);
// 	free_sphere(sp);
// 	free_intersect(i);
// 	free_intersect(i2);
// 	free_ray(res);
// 	free_ray(res1);
// }

// int	main()
// {
// 	t_tuple	*point;
// 	t_tuple	*res;

// 	point = create_point(0, 1, 0);
// 	res = matrix_rotation_z(point, 90);
// 	print_tuple(res);
// 	free(point);
// 	free(res);
// 	return (0);
// }

// int	main()
// {
// 	t_tuple	*t;
// 	t_tuple	*res;

// 	t = create_point(2, 3, 4);
// 	res = matrix_reflection(t);
// 	print_tuple(res);
// 	free(t);
// 	free(res);
// 	return (0);
// }

// int	main()
// {
// 	t_matrix	*m;
// 	t_matrix	*m2;

// 	m = create_matrix(4, 4);
// 	set_mat_value(m, -5, 0, 0);
// 	set_mat_value(m, 2, 0, 1);
// 	set_mat_value(m, 6, 0, 2);
// 	set_mat_value(m, -8, 0, 3);
// 	set_mat_value(m, 1, 1, 0);
// 	set_mat_value(m, -5, 1, 1);
// 	set_mat_value(m, 1, 1, 2);
// 	set_mat_value(m, 8, 1, 3);
// 	set_mat_value(m, 7, 2, 0);
// 	set_mat_value(m, 7, 2, 1);
// 	set_mat_value(m, -6, 2, 2);
// 	set_mat_value(m, -7, 2, 3);
// 	set_mat_value(m, 1, 3, 0);
// 	set_mat_value(m, -3, 3, 1);
// 	set_mat_value(m, 7, 3, 2);
// 	set_mat_value(m, 4, 3, 3);
// 	m2 = matrix_inverse(m);
// 	print_mat(m2);
// 	free_matrix(m);
// 	free_matrix(m2);
// 	return (0);
// }

// int	main()
// {
// 	t_matrix	*m1;
// 	t_matrix	*m2;

// 	m1 = create_matrix(4, 4);
// 	set_mat_value(m1, 1, 0, 0);
// 	set_mat_value(m1, 2, 0, 1);
// 	set_mat_value(m1, 3, 0, 2);
// 	set_mat_value(m1, 4, 0, 3);
// 	set_mat_value(m1, 2, 1, 0);
// 	set_mat_value(m1, 4, 1, 1);
// 	set_mat_value(m1, 4, 1, 2);
// 	set_mat_value(m1, 2, 1, 3);
// 	set_mat_value(m1, 8, 2, 0);
// 	set_mat_value(m1, 6, 2, 1);
// 	set_mat_value(m1, 4, 2, 2);
// 	set_mat_value(m1, 1, 2, 3);
// 	set_mat_value(m1, 1, 3, 3);
// 	print_mat(m1);
// 	m2 = submatrix(m1, 1, 1);
// 	print_mat(m2);
// 	free_matrix(m1);
// 	free_matrix(m2);
// 	return (0);
// }
