/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:08 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/09 17:37:09 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_ray	*res;

	res = create_ray(create_temp_tuple(1, 2, 3, 1), create_temp_tuple(4, 5, 6, 0));
	print_tuple(res->point);
	print_tuple(res->direction);
	free_ray(res);
}

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
