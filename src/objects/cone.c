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
#include "mlx_dat.h"

double	hit_cone(t_cone *co, t_ray *ray, double r_max, t_hit_dat *rec)
{
	double	d_dot_d;
	double	d_dot_v;
	double	A;
	double	t;
	int		hit_type;
	double	final_m;
	hit_type = 0;
	d_dot_d = vec3_dot(ray->vec, ray->vec);
	d_dot_v = vec3_dot(ray->vec, co->axis);
	A = d_dot_d - (co->constant_k * d_dot_v * d_dot_v);

	t_vec3	delta_p = vec3_sub(ray->point, co->pos);
	double	d_dot_dp = vec3_dot(ray->vec, delta_p);
	d_dot_v = vec3_dot(ray->vec, co->axis);
	double	dp_dot_v = vec3_dot(delta_p, co->axis);
	double	B = 2.0 * (d_dot_dp - (co->constant_k * d_dot_v * dp_dot_v));

	double	delta_p_sq = vec3_dot(delta_p, delta_p);
	double	C = delta_p_sq - (co->constant_k * dp_dot_v * dp_dot_v);

	double discriminant = (B * B) - (4.0 * A * C);
	if (discriminant < 0.0001)
	return (-1.0);
	double sqrt_d = sqrt(discriminant);
	double t1 = (-B - sqrt_d) / (2.0 * A);
	double t2 = (-B + sqrt_d) / (2.0 * A);
	double t3;
	t_vec3	cap_center = vec3_add(co->pos, vec3_mul(co->axis, co->height));
	double denom = vec3_dot(ray->vec, co->axis);
	t3 = 0;
	t = 0.001;
	if (!(fabs(denom) < 1e-8))
	{
		t3 = vec3_dot(vec3_sub(cap_center, ray->point), co->axis) / denom;
		if (t3 <= 0.001 || t3 >= r_max)
			t3 = 0;
		t_vec3	hit_point = ray_pos(ray, t3);
		if (vec3_len_sq(vec3_sub(hit_point, cap_center)) > co->radius * co->radius)
			t3 = 0;
	}
	t = r_max;
	final_m = 0.0;
	if (t1 > 0.001 && t1 < t)
	{
		double m1 = vec3_dot(vec3_sub(ray_pos(ray, t1), co->pos), co->axis);
		if (m1 >= 0.0 && m1 <= co->height)
		{
			hit_type = 1;
			t = t1;
			final_m = m1;
		}
	}
	if (t2 > 0.001 && t2 < t)
	{
		double m2 = vec3_dot(vec3_sub(ray_pos(ray, t2), co->pos), co->axis);
		if (m2 >= 0.0 && m2 <= co->height)
		{
			hit_type = 1;
			t = t2;
			final_m = m2;
		}
	}
	if (t3 > 0.001 && t3 < t)
	{
		hit_type = 2;
		t = t3;
	}
	if (hit_type == 0)
		return (-1.0);
	rec->t = t;
	rec->point = ray_pos(ray, t);
	if (hit_type == 1)
	{
		t_vec3	outward_normal = unit_vec3(vec3_sub(vec3_sub(rec->point, co->pos),
			vec3_mul(co->axis, co->constant_k * final_m)));
		set_face_normal(ray, &outward_normal, rec);
	}
	else if (hit_type == 2)
		set_face_normal(ray, &co->axis, rec);
	rec->mat = co->material;
	rec->color = co->color;
	return (t);
}

double	cone_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec)
{
	return (hit_cone(&self->cone, ray, r_max, rec));
}

void	cone_translate(t_objects *self, int key)
{
	if (key == XK_Up)
		self->cone.pos.y += MOVE_Y;
	else if (key == XK_Down)
		self->cone.pos.y -= MOVE_Y;
	else if (key == XK_Left)
		self->cone.pos.x -= MOVE_X;
	else if (key == XK_Right)
		self->cone.pos.x += MOVE_X;
	else if (key == XK_equal)
		self->cone.radius += EXPAND;
	else if (key == XK_minus)
		self->cone.radius -= SHIRNK;
}

void	cone_rotate(t_objects *self, int key)
{
	if (key == XK_bracketleft)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis, create_vec3(0.0, 1.0, 0.0), -0.1));
	else if (key == XK_bracketright)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis, create_vec3(0.0, 1.0, 0.0), 0.1));
	else if (key == XK_semicolon)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis, create_vec3(1.0, 0.0, 0.0), -0.1));
	else if (key == XK_apostrophe)
		self->cone.axis = unit_vec3(vec3_rotate(self->cone.axis, create_vec3(1.0, 0.0, 0.0), 0.1));
}