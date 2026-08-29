/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 10:44:44 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include <math.h>

static bool	gtost(double t_cmp, double gt, double st)
{
	return ((t_cmp < st) || (t_cmp > gt));
}

void	hit_cylinder_tube(t_cylinder_hit *c, t_cylinder_args *a)
{
	t_cylinder	*cy;

	cy = a->cy;
	c->half_axis = vec_mul(cy->axis, cy->height / 2.0);
	c->top_center = vec_add(cy->center, c->half_axis);
	c->bot_center = vec_sub(cy->center, c->half_axis);
	c->neg_axis = vec_mul(cy->axis, -1.0);
	c->x = vec_sub(a->ray->point, cy->center);
	c->d_dot_v = vec_dot(a->ray->vec, cy->axis);
	c->x_dot_v = vec_dot(c->x, cy->axis);
	c->a = vec_dot(a->ray->vec, a->ray->vec) - (c->d_dot_v * c->d_dot_v);
	c->b = 2.0 * (vec_dot(a->ray->vec, c->x)
			- (c->d_dot_v * c->x_dot_v));
	c->c = vec_dot(c->x, c->x) - (c->x_dot_v * c->x_dot_v)
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
