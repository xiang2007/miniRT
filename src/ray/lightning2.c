/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:06:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/color.h"

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

static void	add_recursive_light(t_recurse_l_hit *t, t_recurse_args *args)
{
	t->light_dir = unit_vec3(sub_point(t->obj->light.cords,
				args->rec->point));
	t->alignment = fmax(vec3_dot(t->out_dir, t->light_dir), 0.0);
	if (t->alignment <= t->accept_cos)
		return ;
	t->shadow_ray = ray(vec3_add(args->rec->point,
				vec3_mul(t->out_dir, 0.01)), t->light_dir);
	t->distance = vec3_len(sub_point(t->obj->light.cords, args->rec->point));
	if (shadow_hit(args->world, &t->shadow_ray,
			t->distance, args->rec->hit_obj))
		return ;
	if (args->fuzz < 1e-6)
		t->intensity = 1.0;
	else
		t->intensity = (t->alignment - t->accept_cos)
			/ (1.0 - t->accept_cos);
	t->result = color_add(t->result, color_mul_n(
				color_mul(args->tint, t->obj->light.color),
				light_attenuation(t->obj->light, t->distance) * t->intensity));
}

t_color	recursive_light_hits(t_recurse_args args)
{
	t_recurse_l_hit	t;

	t.result = create_color(0, 0, 0);
	t.out_dir = unit_vec3(args.outgoing->vec);
	t.accept_cos = 1.0 - args.fuzz;
	t.obj = args.world->objs;
	while (t.obj)
	{
		if (t.obj->type == OBJ_LIGHT)
			add_recursive_light(&t, &args);
		t.obj = t.obj->next;
	}
	return (t.result);
}
