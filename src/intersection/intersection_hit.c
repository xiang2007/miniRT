/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:27:48 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/02 16:27:57 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "sphere.h"
#include "ray.h"
#include <math.h>

double	hit_sphere(t_sphere *sp, t_ray *r)
{
	t_vec3	ori_center;
	double	a;
	double	h;
	double	c;
	double	d;

	ori_center = vec_sub(sp->point, r->point);
	a = vec_len_sq(r->vec);
	h = vec_dot(r->vec, ori_center);
	c = vec_len_sq(ori_center) - pow(sp->radius, 2.0);
	d = pow(h, 2.0) - a * c;
	if (d < 0)
		return (-1);
	return ((h - sqrt(d)) / a);
}

