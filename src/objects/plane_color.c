/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:08:45 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/09/02 16:08:45 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"

static t_color	lerp_colour(t_color base, t_color tint, float strength)
{
	t_color	final;

	final.r = (base.r * (1.0 - strength)) + (tint.r * strength);
	final.g = (base.g * (1.0 - strength)) + (tint.g * strength);
	final.b = (base.b * (1.0 - strength)) + (tint.b * strength);
	return (final);
}

static bool	plane_tinted_cell(const t_plane *p, const t_vec3 *point,
		const t_vec3 *normal)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	hit_vector;
	float	local_u;
	float	local_v;

	if (fabs(normal->y) > 0.999)
		u_axis = create_vec3(1, 0, 0);
	else
		u_axis = create_vec3(0, 1, 0);
	u_axis = unit_vec3(vec3_cross(u_axis, *normal));
	v_axis = unit_vec3(vec3_cross(*normal, u_axis));
	hit_vector = vec3_sub(*point, p->center);
	local_u = vec3_dot(hit_vector, u_axis);
	local_v = vec3_dot(hit_vector, v_axis);
	return (abs(((int)floor(local_u) + (int)floor(local_v)) % 2) == 0);
}

static t_color	plane_checker(const t_plane *p, const t_vec3 *point,
		const t_vec3 *normal, t_lambertian *lam)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	rel;
	double	u;
	double	v;

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

t_color	plane_color(const t_plane *p, const t_vec3 *point,
		const t_vec3 *normal)
{
	t_lambertian	*lam;

	if (plane_tinted_cell(p, point, normal))
		return (lerp_colour(p->color, create_vec3(0.1, 0.1, 0.1), 0.3));
	lam = (t_lambertian *)p->material;
	if (!lam || lam->base.scatter != lambertian_scatter
		|| lam->checker_size <= 0.0)
		return (p->color);
	return (plane_checker(p, point, normal, lam));
}
