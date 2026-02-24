/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:32:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 15:15:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*transform_ray(t_ray *r, t_matrix *m)
{
	t_tuple		*new_ori;
	t_tuple		*new_dir;
	t_ray		*new_ray;

	if (!r)
		return (NULL);
	new_ori = mult_matrix_tuple(m, r->origin);
	new_dir = mult_matrix_tuple(m, r->direction);
	new_ray = create_ray(new_ori, new_dir);
	free(new_ori);
	free(new_dir);
	return (new_ray);
}

t_ray	*scale_ray(t_ray *r, t_matrix *m)
{
	t_tuple	*new_ori;
	t_tuple	*new_dir;
	t_ray	*res;

	if (!r || !m)
		return (NULL);
	new_ori = mult_matrix_tuple(m, r->origin);
	new_dir = mult_matrix_tuple(m, r->direction);
	res = create_ray(new_ori, new_dir);
	free(new_ori);
	free(new_dir);
	return (res);
}
