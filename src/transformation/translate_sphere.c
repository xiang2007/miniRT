/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:06:39 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 10:16:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*translate_sphere(t_sphere *s, double x, double y, double z)
{
	t_sphere	*res;
	t_tuple		*translate_res;

	if (!s)
		return (NULL);
	translate_res = matrix_translation(s->point, x, y, z);
	res = create_sphere(s->id);
	free(res->point);
	res->point = translate_res;
	return (res);
}

// t_sphere	*scale_ray(t_sphere *s, double x, double y, double z)
// {
// 	t_sphere	*res;

// 	if (!s)
// 		return (NULL);
// 	res = create_sphere(s->id);
// 	res->point = 
// }