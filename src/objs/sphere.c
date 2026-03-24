/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:33:33 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 15:24:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	sphere(t_point3 center, double radius, t_color col)
{
	t_sphere	sphere;

	sphere.point = center;
	sphere.radius = radius;
	sphere.color = col.color;
	return (sphere);
}

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

bool front_face(t_cylinder c, t_ray ray, double t)
{
	bool		front;
	t_point3	hit_point;
	t_vec3		out;

	hit_point = add_vec(ray.point, scale_vec(ray.vec, t));
	out = unit_vec(sub_vec(hit_point, c.center));
	front = (dot_vec(ray.vec, out) < 0);
	return (front);
}