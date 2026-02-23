/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:32:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/23 19:50:50 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*transform_ray(t_ray *r, t_matrix *m)
{
	t_matrix	*new_ori_m;
	t_matrix	*new_dir_m;
	t_tuple		*new_ori;
	t_tuple		*new_dir;
	t_ray		*new_ray;

	if (!r)
		return (NULL);
	new_ori_m = (m, r->origin);
	new_dir_m = mult_matrix_w_tuple(m, r->direction);
	new_ori = matrix_to_point(new_ori_m);
	new_dir = matrix_to_vector(new_dir_m);
	new_ray = create_ray(new_ori, new_dir);
	free(new_ori);
	free(new_dir);
	free_matrix(new_ori_m);
	free_matrix(new_dir_m); 
	return (new_ray);
}

t_ray	*scale_ray(t_ray *r, t_matrix *m)
{
	t_ray	*rs;
	t_tuple	*t;
	t_tuple	*t1;
	t_tuple	*t2;

	if (!r)
		return (NULL);
	t = create_point(x, y, z);
	t1 = mult_2_tuple(r->origin, t);
	t2 = mult_2_tuple(r->direction, t);
	rs = create_ray(t1, t2);
	free(t1);
	free(t2);
	free(t);
	return (rs);
}
