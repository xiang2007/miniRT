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
#include "vec3.h"
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>

static void	get_sphere_uv(t_point3 local_p, double *u, double *v)
{
	double	phi;
	double	theta;
	double	clamped_y;

	clamped_y = fmax(-1.0, fmin(1.0, local_p.y));
	phi = atan2(local_p.z, local_p.x);
	theta = asin(clamped_y);
	*u = 1.0 - (phi / (2.0 * PI) + 0.5);
	*v = theta / PI + 0.5;
}

static t_vec3	perturb_sphere_normal(t_vec3 local_p, double strength)
{
	t_sphere_uv	map;
	t_vec3		tangent;
	t_vec3		bitangent;
	t_vec3		perturbed;

	get_sphere_uv(local_p, &map.u, &map.v);
	map.du = (bump_height(map.u + EPS, map.v) - bump_height(map.u, map.v))
		/ EPS;
	map.dv = (bump_height(map.u, map.v + EPS) - bump_height(map.u, map.v))
		/ EPS;
	if (fabs(local_p.y) > 0.999)
		tangent = create_vec3(1.0, 0.0, 0.0);
	else
		tangent = unit_vec3(create_vec3(-local_p.z, 0.0, local_p.x));
	bitangent = vec3_cross(local_p, tangent);
	perturbed = vec3_sub(local_p, vec3_mul(tangent, map.du * strength));
	perturbed = vec3_sub(perturbed, vec3_mul(bitangent, map.dv * strength));
	return (unit_vec3(perturbed));
}

static void	calculate_sphere_normal(t_ray *ray, t_hit_dat *rec, t_sphere *sp)
{
	rec->normal = vec3_div(vec3_sub(rec->point, sp->point), sp->radius);
	if (sp->has_bump == true)
		rec->normal = perturb_sphere_normal(rec->normal, STRENGTH);
	set_face_normal(ray, &rec->normal, rec);
}

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
	calculate_sphere_normal(ray, rec, &sp);
	rec->mat = sp.material;
	return (dat.root);
}

void	sphere_translate(t_objects *self, int key)
{
	if (key == XK_w)
		self->sphere.point.y += MOVE_Y;
	else if (key == XK_s)
		self->sphere.point.y -= MOVE_Y;
	else if (key == XK_a)
		self->sphere.point.x -= MOVE_X;
	else if (key == XK_d)
		self->sphere.point.x += MOVE_X;
	else if (key == XK_q)
		self->sphere.point.z -= MOVE_Y;
	else if (key == XK_e)
		self->sphere.point.z += MOVE_X;
	else if (key == XK_equal)
		self->sphere.radius += EXPAND;
	else if (key == XK_minus)
		self->sphere.radius -= SHIRNK;
}
