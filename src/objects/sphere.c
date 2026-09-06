/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:33:33 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/09 13:49:17 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "objects.h"
#include "material.h"
#include <X11/keysym.h>

/**
 * @brief Calculates whether the ray hits the sphere
 *
 * @param sp sphere struct
 * @param r ray struct
 * @param r_max closest hit point I think
 * @param rec record hit struct
 * @return root value
 */
double	sphere_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec)
{
	t_sphere_hit	dat;
	t_sphere		sp;

	sp = self->sphere;
	dat.ori_center = vec3_sub(sp.point, ray->point);
	dat.a = vec3_len_sq(ray->vec);
	dat.h = vec3_dot(ray->vec, dat.ori_center);
	dat.c = vec3_len_sq(dat.ori_center) - pow(sp.radius, 2.0);
	dat.d = (dat.h * dat.h) - dat.a * dat.c;
	if (dat.d < 0)
		return (-1);
	dat.root = (dat.h - sqrt(dat.d)) / dat.a;
	if (dat.root <= 0.001 || r_max <= dat.root)
	{
		dat.root = (dat.h + sqrt(dat.d)) / dat.a;
		if (dat.root <= 0.001 || r_max <= dat.root)
			return (0);
	}
	rec->t = dat.root;
	rec->point = ray_pos(ray, dat.root);
	rec->color = sp.color;
	dat.outward_normal = vec3_div(vec3_sub(rec->point, sp.point), sp.radius);
	set_face_normal(ray, &dat.outward_normal, rec);
	rec->mat = sp.material;
	return (dat.root);
}

void	sphere_translate(t_objects *self, int key)
{
	if (key == XK_Up)
		self->sphere.point.y += MOVE_Y;
	else if (key == XK_Down)
		self->sphere.point.y -= MOVE_Y;
	else if (key == XK_Left)
		self->sphere.point.x -= MOVE_X;
	else if (key == XK_Right)
		self->sphere.point.x += MOVE_X;
	else if (key == XK_equal)
		self->sphere.radius += EXPAND;
	else if (key == XK_minus)
		self->sphere.radius -= SHIRNK;
}