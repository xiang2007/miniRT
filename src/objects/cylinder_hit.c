/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hit.c                                     :+:      :+:    :+:   */
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
