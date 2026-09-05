/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 20:55:43 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/color.h"
#include "../../includes/material.h"
#include "minirt.h"

bool	shadow_hit(t_world *w, t_ray *ray, double t_max, t_objects *skip)
{
	t_objects	*t;
	t_hit_dat	rec;

	t = w->objs;
	while (t)
	{
		if (t != skip && !material_is_transparent(t))
		{
			rec = (t_hit_dat){0};
			if (t->type == OBJ_SPHERE
				&& hit_sphere(&t->sphere, ray, t_max, &rec) > 0)
				return (true);
			if (t->type == OBJ_CYLINDER
				&& hit_cylinder(&t->cylinder, ray, t_max, &rec) > 0)
				return (true);
			if (t->type == OBJ_PLANE
				&& hit_plane(&t->plane, ray, t_max, &rec) > 0)
				return (true);
			if (t->type == OBJ_CONE
				&& hit_cone(&t->cone, ray, t_max, &rec) > 0)
				return (true);
		}
		t = t->next;
	}
	return (false);
}