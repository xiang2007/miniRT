/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 05:19:48 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	material_is_transparent(t_objects *o)
{
	t_material	*mat;

	mat = NULL;
	if (o->type == OBJ_SPHERE)
		mat = o->sphere.material;
	else if (o->type == OBJ_CYLINDER)
		mat = o->cylinder.material;
	else if (o->type == OBJ_PLANE)
		mat = o->plane.material;
	else if (o->type == OBJ_CONE)
		mat = o->cone.material;
	return (mat && mat->scatter == dielectric_scatter);
}
