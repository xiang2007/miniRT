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
#include "mlx_dat.h"
#include "vec3.h"

static bool	gtost(double t_cmp, double gt, double st)
{
	return ((t_cmp < st) || (t_cmp > gt));
}

void	hit_cylinder_tube(t_cylinder_hit *c, t_cylinder_args *a)
{
	t_cylinder	*cy;

	cy = a->cy;
	c->half_axis = vec3_mul(cy->axis, cy->height / 2.0);
	c->top_center = vec3_add(cy->center, c->half_axis);
	c->bot_center = vec3_sub(cy->center, c->half_axis);
	c->neg_axis = vec3_mul(cy->axis, -1.0);
	c->x = vec3_sub(a->ray->point, cy->center);
	c->d_dot_v = vec3_dot(a->ray->vec, cy->axis);
	c->x_dot_v = vec3_dot(c->x, cy->axis);
	c->a = vec3_dot(a->ray->vec, a->ray->vec) - (c->d_dot_v * c->d_dot_v);
	c->b = 2.0 * (vec3_dot(a->ray->vec, c->x)
			- (c->d_dot_v * c->x_dot_v));
	c->c = vec3_dot(c->x, c->x) - (c->x_dot_v * c->x_dot_v)
		- (cy->radius * cy->radius);
	c->d = (c->b * c->b) - (4 * c->a * c->c);
	c->t_tube = -1.0;
}

void	hit_cylinder_tube2(t_cylinder_hit *c, t_cylinder_args *a)
{
	c->m = 0;
	if (c->d < 0.0 || fabs(c->a) <= 1e-12)
		return ;
	c->root = (-c->b - sqrt(c->d)) / (2.0 * c->a);
	if (gtost(c->root, a->r_max, 0.01))
		c->root = (-c->b + sqrt(c->d)) / (2.0 * c->a);
	if (gtost(c->root, a->r_max, 0.01))
		c->root = -1.0;
	if (c->root > 0.0)
	{
		c->m = (c->d_dot_v * c->root) + c->x_dot_v;
		if (gtost(c->m, a->cy->height / 2.0, -(a->cy->height / 2.0)))
			c->root = (-c->b + sqrt(c->d)) / (2.0 * c->a);
	}
	if (gtost(c->root, a->r_max, 0.01))
		c->root = -1.0;
	if (c->root > 0.0)
	{
		c->m = (c->d_dot_v * c->root) + c->x_dot_v;
		if (gtost(c->m, a->cy->height / 2.0, -(a->cy->height / 2.0)))
			c->root = -1.0;
	}
	c->t_tube = c->root;
}

void	hit_cylinder_caps(t_cylinder_hit *c, t_cylinder_args *a)
{
	c->t_top = hit_cap(a, &c->top_center, &a->cy->axis);
	c->t_bot = hit_cap(a, &c->bot_center, &c->neg_axis);
	c->t_best = c->t_tube;
	c->outward_normal = create_vec3(0, 0, 0);
	if (c->t_top > 0.0 && (c->t_best < 0.0 || c->t_top < c->t_best))
	{
		c->t_best = c->t_top;
		c->outward_normal = a->cy->axis;
	}
	if (c->t_bot > 0.0 && (c->t_best < 0.0 || c->t_bot < c->t_best))
	{
		c->t_best = c->t_bot;
		c->outward_normal = c->neg_axis;
	}
}

double	hit_cap(t_cylinder_args *args, const t_vec3 *cap_center,
		const t_vec3 *normal)
{
	double	denom;
	double	t;
	t_vec3	hit_point;

	denom = vec3_dot(args->ray->vec, *normal);
	if (fabs(denom) < 1e-8)
		return (-1.0);
	t = vec3_dot(vec3_sub(*cap_center, args->ray->point), *normal) / denom;
	if (t <= 0.001 || t >= args->r_max)
		return (-1.0);
	hit_point = ray_pos(args->ray, t);
	if (vec3_len_sq(vec3_sub(hit_point, *cap_center))
		> args->cy->radius * args->cy->radius)
		return (-1.0);
	return (t);
}

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
	if (key == XK_Up)
		self->cylinder.center.y += MOVE_Y;
	else if (key == XK_Down)
		self->cylinder.center.y -= MOVE_Y;
	else if (key == XK_Left)
		self->cylinder.center.x -= MOVE_X;
	else if (key == XK_Right)
		self->cylinder.center.x += MOVE_X;
	else if (key == XK_equal)
		self->cylinder.radius += EXPAND;
	else if (key == XK_minus)
		self->cylinder.radius -= SHIRNK;
}

void	cylinder_rotate(t_objects *self, int key)
{
	// t_vec3	right;

	// right = get_object_right(self->cylinder.axis);
	// if (key == XK_bracketleft)
	// 	self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, right, -0.1));
	// else if (key == XK_bracketright)
	// 	self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, right, 0.1));
	// else if (key == XK_semicolon)
	// 	self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, get_object_up(self->cylinder.axis, right), -0.1));
	// else if (key == XK_apostrophe)
	// 	self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, get_object_up(self->cylinder.axis, right), 0.1));
	if (key == XK_bracketleft)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, create_vec3(0.0, 1.0, 0.0), -0.1));
	else if (key == XK_bracketright)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, create_vec3(0.0, 1.0, 0.0), 0.1));
	else if (key == XK_semicolon)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, create_vec3(1.0, 0.0, 0.0), -0.1));
	else if (key == XK_apostrophe)
		self->cylinder.axis = unit_vec3(vec3_rotate(self->cylinder.axis, create_vec3(1.0, 0.0, 0.0), 0.1));
}

// Inside your keyboard hook, pass the camera struct to your object rotation logic

// if (keycode == KEY_PITCH_UP)
// {
// 	// Rotate the object around the CAMERA'S Right vector (cam->u)
// 	co->axis = rodrigues_rotate(co->axis, cam->u, 0.1);
// 	co->axis = unit_vec3(co->axis);
// }

// if (keycode == KEY_YAW_LEFT)
// {
// 	// Rotate the object around the CAMERA'S Up vector (cam->v)
// 	co->axis = rodrigues_rotate(co->axis, cam->v, 0.1);
// 	co->axis = unit_vec3(co->axis);
// }

// if (keycode == KEY_ROLL_RIGHT)
// {
// 	// Rotate the object around the CAMERA'S Forward vector (cam->w)
// 	// (Note: cam->w points backwards, so you may need -0.1 depending on desired spin direction)
// 	co->axis = rodrigues_rotate(co->axis, cam->w, 0.1);
// 	co->axis = unit_vec3(co->axis);
// }