/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:08:45 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/09/02 16:08:45 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_dat.h"
#include "objects.h"
#include "vec3.h"
#include "ray.h"
#include <X11/keysym.h>

static t_color	lerp_colour(t_color base, t_color tint, float strength)
{
	t_color	final;

	final.r = (base.r * (1.0 - strength)) + (tint.r * strength);
	final.g = (base.g * (1.0 - strength)) + (tint.g * strength);
	final.b = (base.b * (1.0 - strength)) + (tint.b * strength);
	return (final);
}

static t_color	plane_color(const t_plane *p, const t_vec3 *point,
		const t_vec3 *normal)
{
	t_lambertian	*lam;
	t_vec3			tangent;
	t_vec3			bitangent;
	t_vec3			rel;
	double			u;
	double			v;

	// checkerbox
	t_vec3	helper = (fabs(normal->y) > 0.999) ? create_vec3(1, 0, 0) : create_vec3(0, 1, 0);
	t_vec3	u_axis = unit_vec3(vec3_cross(helper, *normal));
	t_vec3	v_axis = unit_vec3(vec3_cross(*normal, u_axis));
	t_vec3 hit_vector = vec3_sub(*point, p->center);
	float local_u = vec3_dot(hit_vector, u_axis);
	float local_v = vec3_dot(hit_vector, v_axis);
	float	scale = 1.0;
	int		check_u = (int)floor(local_u * scale);
	int		check_v = (int)floor(local_v * scale);
	if (abs((check_u + check_v) % 2) == 0)
	{
		return (lerp_colour(p->color, (t_color) {.r = 0.1, .g = 0.1, .b = 0.1}, 0.3));
	}
	
	lam = (t_lambertian *)p->material;
	if (!lam || lam->base.scatter != lambertian_scatter
		|| lam->checker_size <= 0.0)
		return (p->color);
	if (fabs(normal->y) < 0.99)
		tangent = unit_vec3(vec3_cross(*normal, create_vec3(0, 1, 0)));
	else
		tangent = unit_vec3(vec3_cross(*normal, create_vec3(1, 0, 0)));
	bitangent = vec3_cross(*normal, tangent);
	rel = vec3_sub(*point, p->center);
	u = vec3_dot(rel, tangent);
	v = vec3_dot(rel, bitangent);
	if ((((int)floor(u / lam->checker_size))
			+ ((int)floor(v / lam->checker_size))) % 2 == 0)
		return (lam->albedo);
	return (lam->checker_color);
}

/**
 * @brief Calculates whether the ray hits the plane
 *
 * @param p the plane struct
 * @param ray the ray struct
 * @param r_max closest hit I think
 * @param rec the record hit struct
 * @return the root value
 */
double	hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec)
{
	double	t;
	double	d;
	t_vec3	p0;
	t_vec3	normal;

	normal = unit_vec3(p->axis);
	d = vec3_dot(normal, ray->vec);
	if (fabs(d) < __DBL_EPSILON__)
		return (-1);
	p0 = vec3_sub(p->center, ray->point);
	t = vec3_dot(p0, normal) / d;
	if (t <= __DBL_EPSILON__ || t >= r_max)
		return (-1);
	rec->t = t;
	rec->point = ray_pos(ray, t);
	set_face_normal(ray, &normal, rec);
	rec->mat = p->material;

	rec->color = plane_color(p, &rec->point, &normal);
	return (t);
}

double	plane_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec)
{
	return (hit_plane(&self->plane, ray, r_max, rec));
}

void	plane_translate(t_objects *self, int key)
{
	if (key == XK_Up)
		self->plane.center.y += MOVE_Y;
	else if (key == XK_Down)
		self->plane.center.y -= MOVE_Y;
	else if (key == XK_Left)
		self->plane.center.x -= MOVE_X;
	else if (key == XK_Right)
		self->plane.center.x += MOVE_X;
}

void	plane_rotate(t_objects *self, int key)
{
	if (key == XK_bracketleft)
		self->plane.axis = unit_vec3(vec3_rotate(self->plane.axis, create_vec3(0.0, 1.0, 0.0), -0.1));
	else if (key == XK_bracketright)
		self->plane.axis = unit_vec3(vec3_rotate(self->plane.axis, create_vec3(0.0, 1.0, 0.0), 0.1));
	else if (key == XK_semicolon)
		self->plane.axis = unit_vec3(vec3_rotate(self->plane.axis, create_vec3(1.0, 0.0, 0.0), -0.1));
	else if (key == XK_apostrophe)
		self->plane.axis = unit_vec3(vec3_rotate(self->plane.axis, create_vec3(1.0, 0.0, 0.0), 0.1));
}
