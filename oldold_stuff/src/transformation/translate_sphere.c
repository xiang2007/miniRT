/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:06:39 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 14:02:04 by wshou-xi         ###   ########.fr       */
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

t_sphere	*scale_sphere(t_sphere *s, double x, double y, double z)
{
	t_sphere	*new_sphere;


	if (!s)
		return (NULL);
	new_sphere = create_sphere(s->id);
	if (!new_sphere)
		return(NULL);
	free(new_sphere->point);
	new_sphere->point = matrix_scaling(s->point, x, y, z);
	print_tuple(new_sphere->point);
	return (new_sphere);
}
