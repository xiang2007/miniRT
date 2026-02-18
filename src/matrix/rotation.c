/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:58:06 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 23:25:58 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*rotation_x(t_d	r)
{
	t_matrix	*tr;
	t_d			**m;
	t_d			c;
	t_d			s;

	tr = create_matrix(4, 4);
	if (!tr)
		return (NULL);
	set_identity_matrix(tr);
	m = tr->matrix;
	c = cos(r);
	s = sin(r);
	m[1][1] = c;
	m[1][2] = -s;
	m[2][1] = s;
	m[2][2] = c;
	return (tr);
}

t_tuple	*rot_x(t_tuple *p, t_d radian)
{
	t_matrix	*fq;
	t_matrix	*point;
	t_matrix	*res2;
	t_tuple		*tup;

	if (!p)
		return (NULL);
	point = point_to_matrix(p);
	fq = rotation_x(radian);
	res2 = dynamic_mult_matrix(fq, point);
	tup = create_point(res2->matrix[0][0], res2->matrix[1][0],
			res2->matrix[2][0]);
	free_matrix(res2);
	free_matrix(fq);
	free_matrix(point);
	return (tup);
}

t_matrix	*rotation_y(t_d	r)
{
	t_matrix	*tr;
	t_d			**m;
	t_d			c;
	t_d			s;

	tr = create_matrix(4, 4);
	if (!tr)
		return (NULL);
	set_identity_matrix(tr);
	m = tr->matrix;
	c = cos(r);
	s = sin(r);
	m[0][0] = c;
	m[0][2] = s;
	m[2][0] = -s;
	m[2][2] = c;
	return (tr);
}

t_tuple	*rot_y(t_tuple *p, t_d radian)
{
	t_matrix	*fq;
	t_matrix	*point;
	t_matrix	*res2;
	t_tuple		*tup;

	if (!p)
		return (NULL);
	point = point_to_matrix(p);
	fq = rotation_y(radian);
	res2 = dynamic_mult_matrix(fq, point);
	tup = create_point(res2->matrix[0][0], res2->matrix[1][0],
			res2->matrix[2][0]);
	free_matrix(res2);
	free_matrix(fq);
	free_matrix(point);
	return (tup);
}
