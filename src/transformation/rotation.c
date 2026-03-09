/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:15:55 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/09 13:56:46 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	*matrix_rotation_y_calc(double deg)
{
	double		rad;
	double		**mt;
	t_matrix	*m;

	rad = (deg / 180) * PI;
	m = create_identity_matrix();
	mt = m->matrix;
	mt[0][0] = cos(rad);
	mt[0][2] = sin(rad);
	mt[2][0] = -(sin(rad));
	mt[2][2] = (cos(rad));
	return (m);
}

static t_matrix	*matrix_rotation_x_calc(double deg)
{
	double		rad;
	double		**mt;
	t_matrix	*m;

	rad = (deg / 180) * PI;
	m = create_identity_matrix();
	mt = m->matrix;
	mt[1][1] = cos(rad);
	mt[1][2] = -(sin(rad));
	mt[2][1] = sin(rad);
	mt[2][2] = cos(rad);
	return (m);
}

t_tuple	*matrix_rotation_x(t_tuple *p, double deg)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (NULL);
	m = matrix_rotation_x_calc(deg);
	res = mult_tuple_matrix(p, m);
	free_matrix(m);
	return (res);
}

t_tuple	*matrix_rotation_y(t_tuple *p, double deg)
{
	t_tuple		*res;
	t_matrix	*m;

	if (!p)
		return (NULL);
	m = matrix_rotation_y_calc(deg);
	res = mult_tuple_matrix(p, m);
	free_matrix(m);
	return (res);
}

t_tuple	*matrix_rotation_z(t_tuple *p, double deg)
{
	t_tuple		*res;
	t_matrix	*m;
	double		rad;

	rad = (deg / 180) * PI;
	m = create_identity_matrix();
	set_mat_value(m, cos(rad),0 ,0);
	set_mat_value(m, -(sin(rad)),0 ,1);
	set_mat_value(m, sin(rad),1 ,0);
	set_mat_value(m, cos(rad),1 ,1);
	res = mult_tuple_matrix(p, m);
	free_matrix(m);
	return (res);
}
