/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:47:04 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 10:52:34 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*create_camera(int fov, t_d x, t_d y, t_d z)
{
	t_cam	*res;
	t_tuple	*t;

	if (fov < 0 || fov > 180)
		return (NULL);
	res = malloc(sizeof(t_cam));
	if (!res)
		return (NULL);
	res->fov = fov;
	res->x = x;
	res->y = y;
	res->z = z;
	t = create_point(x, y, z);
	res->norm = normalize(t);
	free(t);
	return (res);
}