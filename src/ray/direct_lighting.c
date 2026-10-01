/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 09:19:47 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "color.h"

static void	prepare_light(t_lightning *l, t_hit_dat *rec, t_light light)
{
	*l = (t_lightning){0};
	l->shadow_ori = vec3_add(rec->point, vec3_mul(rec->normal, 0.001));
	l->light_dir = unit_vec3(sub_point(light.cords, rec->point));
	l->light_distance = vec3_len(sub_point(light.cords, rec->point));
	l->shadow_ray = ray(l->shadow_ori, l->light_dir);
}

static t_color	light_color(t_lightning *l, t_hit_dat *rec, t_light light)
{
	l->result = color_mul(material_albedo(rec->mat, rec->color), light.color);
	l->result = color_mul_n(l->result, l->brightness);
	l->result = color_add(l->result, color_mul_n(light.color, l->specular));
	return (l->result);
}

t_color	compute_direct_lighting(t_hit_dat *rec, t_world *w, t_ray *r)
{
	t_objects	*objs;
	t_color		total;
	t_lightning	l;

	total = create_color(0, 0, 0);
	objs = w->objs;
	while (objs)
	{
		if (objs->type == OBJ_LIGHT)
		{
			prepare_light(&l, rec, objs->light);
			if (!shadow_hit(w, &l.shadow_ray, l.light_distance, rec->hit_obj))
			{
				lightning_helper(&l, rec, r, objs->light);
				total = color_add(total, light_color(&l, rec, objs->light));
			}
		}
		objs = objs->next;
	}
	return (total);
}
