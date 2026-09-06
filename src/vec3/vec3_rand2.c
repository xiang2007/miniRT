/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 21:40:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:07:30 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include <math.h>

t_vec3	reflect(const t_vec3 *vec, const t_vec3 *normal)
{
	return (vec3_sub(*vec, vec3_mul(*normal, vec3_dot(*vec, *normal) * 2.0)));
}

t_vec3	refract(const t_vec3 *uv, const t_vec3 *n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = vec3_dot(vec3_mul(*uv, -1.0), *n);
	if (cos_theta > 1.0)
		cos_theta = 1.0;
	r_out_perp = vec3_mul(vec3_add(*uv, vec3_mul(*n, cos_theta)), etai_over_etat);
	r_out_parallel = vec3_mul(*n,
			-1.0 * sqrt(fabs(1.0 - vec3_len_sq(r_out_perp))));
	return (vec3_add(r_out_perp, r_out_parallel));
}

bool	near_zero(t_vec3 *vector)
{
	const double	s = 1e-8;

	return ((fabs(vector->x) < s) && (fabs(vector->y) < s)
		&& (fabs(vector->z) < s));
}

t_vec3	rand_in_unit_sphere(void)
{
	t_vec3	p;
	double	lensq;

	while (1)
	{
		p = vec3_rand(-1.0, 1.0);
		lensq = vec3_len_sq(p);
		if (1e-160 < lensq && lensq < 1.0)
			return (p);
	}
}

t_vec3	rand_on_hemi(const t_vec3 *normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = rand_unit_vec3();
	if (vec3_dot(on_unit_sphere, *normal) > 0.0)
		return (on_unit_sphere);
	return (vec3_mul(on_unit_sphere, -1.0));
}
