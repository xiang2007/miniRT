/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_object2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:36:40 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 15:19:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "minirt.h"
#include "../../includes/parse.h"
#include "../../includes/material.h"
#include "objects.h"

bool	parse_material(char **res, t_objects **o, int idx)
{
	double		ri;
	t_color		cl;
	t_material	*mat;

	ri = 0;
	mat = NULL;
	if ((*o)->type == OBJ_CYLINDER)
		cl = (*o)->cylinder.color;
	else if ((*o)->type == OBJ_SPHERE)
		cl = (*o)->sphere.color;
	else if ((*o)->type == OBJ_PLANE)
		cl = (*o)->plane.color;
	if (ft_strcmp(res[idx], "lambertian") == TRUE)
		mat = create_lambertian(cl);
	else if (ft_strcmp(res[idx], "metal") == TRUE)
	{
		if (res[idx + 1])
			ri = ft_atof(res[idx + 1]);
		else
			ri = 0.3;
		mat = create_metal(cl, ri);
	}
	else if (ft_strcmp(res[idx], "dielectric") == TRUE)
	{
		if (res[idx + 1])
			ri = ft_atof(res[idx + 1]);
		else
			ri = 1.50;
		mat = create_dielectric(ri);
	}
	if (!mat)
		return (free((*o)), free_str_arr(res), FALSE);
	if ((*o)->type == OBJ_CYLINDER)
		(*o)->cylinder.material = mat;
	else if ((*o)->type == OBJ_SPHERE)
		(*o)->sphere.material = mat;
	else if ((*o)->type == OBJ_PLANE)
		(*o)->plane.material = mat;
	return (TRUE);
}

