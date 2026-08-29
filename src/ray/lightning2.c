/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 04:12:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"
#include "../../includes/objects.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include "../../includes/aabb.h"
#include "minirt.h"

t_color	ambient_light(t_world *w)
{
	t_objects	*obj;

	obj = w->objs;
	while (obj)
	{
		if (obj->type == OBJ_AMBIENT)
			return (color_mul_n(obj->ambient.color, obj->ambient.ratio));
		obj = obj->next;
	}
	return (create_color(0, 0, 0));
}