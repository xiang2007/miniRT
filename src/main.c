/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:08 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/05 00:26:22 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_matrix	*m1;
	t_matrix	*m2;

	m1 = create_matrix(4, 4);
	set_mat_value(m1, 1, 0, 0);
	set_mat_value(m1, 2, 0, 1);
	set_mat_value(m1, 3, 0, 2);
	set_mat_value(m1, 4, 0, 3);
	set_mat_value(m1, 2, 1, 0);
	set_mat_value(m1, 4, 1, 1);
	set_mat_value(m1, 4, 1, 2);
	set_mat_value(m1, 2, 1, 3);
	set_mat_value(m1, 8, 2, 0);
	set_mat_value(m1, 6, 2, 1);
	set_mat_value(m1, 4, 2, 2);
	set_mat_value(m1, 1, 2, 3);
	set_mat_value(m1, 1, 3, 3);
	print_mat(m1);
	m2 = submatrix(m1, 1, 1);
	print_mat(m2);
	free_matrix(m1);
	free_matrix(m2);
	return (0);
}
