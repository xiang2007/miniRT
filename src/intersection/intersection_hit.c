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

#include "minirt.h"

double	hit_sphere(t_sphere sphere, t_ray r)
{
	t_vec3	ori_center;
	t_vec3	center;
	double	radius;
	double	a;
	double	b;
	double	c;
	double	d;

	center = sphere.point;
	radius = sphere.radius;
	ori_center = sub_vec(center, r.point);
	a = len_sq(r.vec);
	b = dot_vec(r.vec, ori_center);
	c = len_sq(ori_center) - sq(radius);
	d = sq(b) - a * c;
	if (d < 0)
		return (-1);
	else
		return ((b - sqrt(d)) / a);
}

