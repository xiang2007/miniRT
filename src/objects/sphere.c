/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:33:33 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/02 16:27:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "sphere.h"

t_sphere	sphere(t_point3 center, double radius)
{
	t_sphere	sphere;

	sphere.point = center;
	sphere.radius = radius;
	return (sphere);
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