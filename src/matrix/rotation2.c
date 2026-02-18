/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:55:11 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/15 23:26:07 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*rotation_z(t_d	r)
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
	m[0][1] = -s;
	m[1][0] = s;
	m[1][1] = c;
	return (tr);
}

t_tuple	*rot_z(t_tuple *p, t_d radian)
{
	t_matrix	*fq;
	t_matrix	*point;
	t_matrix	*res2;
	t_tuple		*tup;

	if (!p)
		return (NULL);
	point = point_to_matrix(p);
	fq = rotation_z(radian);
	res2 = dynamic_mult_matrix(fq, point);
	tup = create_point(res2->matrix[0][0], res2->matrix[1][0],
			res2->matrix[2][0]);
	free_matrix(res2);
	free_matrix(fq);
	free_matrix(point);
	return (tup);
}
