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

#include "../../includes/parse.h"
#include "../../includes/material.h"
#include "../../includes/color.h"

bool	parse_material(char **res, t_objects **o)
{
	double	ri;

	ri = 0;
	if (ft_strcmp(res[4], "lambertian") == TRUE)
		(*o)->sphere.material = create_lambertian((*o)->sphere.color);
	else if (ft_strcmp(res[4], "metal") == TRUE)
	{
		if (res[5])
			ri = ft_atof(res[5]);
		else
			ri = 0.3;
		(*o)->sphere.material = create_metal((*o)->sphere.color, ri);
	}
	else if (ft_strcmp(res[4], "dielectric") == TRUE)
	{
		if (res[5])
			ri = ft_atof(res[5]);
		else
			ri = 1.50;
		(*o)->sphere.material = create_dielectric(ri);
	}
	if (!(*o)->sphere.material)
		return (free((*o)), free_str_arr(res), FALSE);
	return (TRUE);
}
