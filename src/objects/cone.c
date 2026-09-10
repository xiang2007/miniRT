/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:24:44 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/09/02 16:24:44 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include <X11/keysym.h>

static double	cone_record(t_cone *co, t_ray *r, t_cone_hit *h,
		t_hit_dat *rec)
{
	if (h->type == 0)
		return (-1.0);
	rec->t = h->t;
	rec->point = ray_pos(r, h->t);
	if (h->type == 1)
	{
		h->normal = unit_vec3(vec3_sub(vec3_sub(rec->point, co->pos),
					vec3_mul(co->axis, co->constant_k * h->m)));
		set_face_normal(r, &h->normal, rec);
	}
	else if (h->type == 2)
		set_face_normal(r, &co->axis, rec);
	rec->mat = co->material;
	rec->color = co->color;
	return (h->t);
}

double	hit_cone(t_cone *co, t_ray *ray, double r_max, t_hit_dat *rec)
{
	t_cone_hit	h;

	h = (t_cone_hit){0};
	if (!cone_roots(co, ray, &h))
		return (-1.0);
	h.t3 = cone_cap(co, ray, r_max);
	h.t = r_max;
	cone_side(co, ray, &h, h.t1);
	cone_side(co, ray, &h, h.t2);
	if (h.t3 > 0.001 && h.t3 < h.t)
	{
		h.type = 2;
		h.t = h.t3;
	}
	return (cone_record(co, ray, &h, rec));
}

double	cone_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec)
{
	return (hit_cone(&self->cone, ray, r_max, rec));
}

void	cone_translate(t_objects *self, int key)
{
	if (key == XK_w)
		self->cone.pos.y += MOVE_Y;
	else if (key == XK_s)
		self->cone.pos.y -= MOVE_Y;
	else if (key == XK_a)
		self->cone.pos.x -= MOVE_X;
	else if (key == XK_d)
		self->cone.pos.x += MOVE_X;
	else if (key == XK_q)
		self->cone.pos.z -= MOVE_Y;
	else if (key == XK_e)
		self->cone.pos.z += MOVE_X;
	else if (key == XK_equal)
		self->cone.radius += EXPAND;
	else if (key == XK_minus)
		self->cone.radius -= SHIRNK;
}

void	cone_rotate(t_objects *self, int key)
{
	if (key == XK_Left)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis,
					create_vec3(0.0, 1.0, 0.0), -0.1));
	else if (key == XK_Right)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis,
					create_vec3(0.0, 1.0, 0.0), 0.1));
	else if (key == XK_Up)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis,
					create_vec3(1.0, 0.0, 0.0), -0.1));
	else if (key == XK_Down)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis,
					create_vec3(1.0, 0.0, 0.0), 0.1));
}
