/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:17:53 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/09/02 16:17:53 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "ray.h"
#include <X11/keysym.h>
#include "vec3.h"

double	hit_cylinder(t_cylinder *cy, t_ray *ray, double r_max, t_hit_dat *rec)
{
	t_cylinder_hit	c;
	t_cylinder_args	a;

	a.cy = cy;
	a.ray = ray;
	a.r_max = r_max;
	a.rec = rec;
	hit_cylinder_tube(&c, &a);
	hit_cylinder_tube2(&c, &a);
	hit_cylinder_caps(&c, &a);
	if (c.t_best < 0.0)
		return (-1.0);
	rec->t = c.t_best;
	rec->point = ray_pos(ray, c.t_best);
	rec->color = cy->color;
	rec->mat = cy->material;
	if (c.t_best == c.t_tube)
	{
		c.p = vec3_add(cy->center, vec3_mul(cy->axis, c.m));
		c.outward_normal = vec3_div(vec3_sub(rec->point, c.p), cy->radius);
	}
	set_face_normal(ray, &c.outward_normal, rec);
	return (c.t_best);
}

double	cylinder_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec)
{
	return (hit_cylinder(&self->cylinder, ray, r_max, rec));
}

void	cylinder_translate(t_objects *self, int key)
{
	if (key == XK_w)
		self->cylinder.center.y += MOVE_Y;
	else if (key == XK_s)
		self->cylinder.center.y -= MOVE_Y;
	else if (key == XK_a)
		self->cylinder.center.x -= MOVE_X;
	else if (key == XK_d)
		self->cylinder.center.x += MOVE_X;
	else if (key == XK_q)
		self->cylinder.center.z -= MOVE_Y;
	else if (key == XK_e)
		self->cylinder.center.z += MOVE_X;
	else if (key == XK_equal)
		self->cylinder.radius += EXPAND;
	else if (key == XK_minus)
		self->cylinder.radius -= SHIRNK;
}

void	cylinder_rotate(t_objects *self, int key)
{
	if (key == XK_Left)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis,
					create_vec3(0.0, 1.0, 0.0), -0.1));
	else if (key == XK_Right)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis,
					create_vec3(0.0, 1.0, 0.0), 0.1));
	else if (key == XK_Up)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis,
					create_vec3(1.0, 0.0, 0.0), -0.1));
	else if (key == XK_Down)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis,
					create_vec3(1.0, 0.0, 0.0), 0.1));
}
