/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:24:44 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/09/02 16:24:44 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

bool	cone_roots(t_cone *co, t_ray *r, t_cone_hit *h)
{
	h->d_dot_v = vec3_dot(r->vec, co->axis);
	h->a = vec3_dot(r->vec, r->vec)
		- (co->constant_k * h->d_dot_v * h->d_dot_v);
	h->delta = vec3_sub(r->point, co->pos);
	h->dp_dot_v = vec3_dot(h->delta, co->axis);
	h->b = 2.0 * (vec3_dot(r->vec, h->delta)
			- (co->constant_k * h->d_dot_v * h->dp_dot_v));
	h->c = vec3_dot(h->delta, h->delta)
		- (co->constant_k * h->dp_dot_v * h->dp_dot_v);
	h->d = (h->b * h->b) - (4.0 * h->a * h->c);
	if (h->d < 0.0001)
		return (false);
	h->d = sqrt(h->d);
	h->t1 = (-h->b - h->d) / (2.0 * h->a);
	h->t2 = (-h->b + h->d) / (2.0 * h->a);
	return (true);
}

double	cone_cap(t_cone *co, t_ray *r, double r_max)
{
	t_vec3	center;
	t_vec3	point;
	double	denom;
	double	t;

	center = vec3_add(co->pos, vec3_mul(co->axis, co->height));
	denom = vec3_dot(r->vec, co->axis);
	t = 0;
	if (!(fabs(denom) < 1e-8))
	{
		t = vec3_dot(vec3_sub(center, r->point), co->axis) / denom;
		if (t <= 0.001 || t >= r_max)
			t = 0;
		point = ray_pos(r, t);
		if (vec3_len_sq(vec3_sub(point, center)) > co->radius * co->radius)
			t = 0;
	}
	return (t);
}

void	cone_side(t_cone *co, t_ray *r, t_cone_hit *h, double t)
{
	double	m;

	if (t > 0.001 && t < h->t)
	{
		m = vec3_dot(vec3_sub(ray_pos(r, t), co->pos), co->axis);
		if (m >= 0.0 && m <= co->height)
		{
			h->type = 1;
			h->t = t;
			h->m = m;
		}
	}
}
