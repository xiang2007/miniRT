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

#include "vec3.h"
#include "sphere.h"
#include "ray.h"
#include "objects.h"
#include "math.h"

t_sphere	sphere(t_point3 center, double radius)
{
	t_sphere	sphere;

	sphere.point = center;
	sphere.radius = radius;
	return (sphere);
}

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

// bool front_face(t_cylinder c, t_ray ray, double t)
// {
// 	bool		front;
// 	t_point3	hit_point;
// 	t_vec3		out;
//
// 	hit_point = add_vec(ray.point, scale_vec(ray.vec, t));
// 	out = unit_vec(sub_vec(hit_point, c.center));
// 	front = (dot_vec(ray.vec, out) < 0);
// 	return (front);
// }