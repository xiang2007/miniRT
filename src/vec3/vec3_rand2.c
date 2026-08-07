/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 21:40:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/07 21:41:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "../../libft/libft.h"
#include <sys/time.h>
#include "../../includes/vec3.h"
#include <math.h>
#include <stdio.h>

t_vec3	reflect(const t_vec3 *vec, const t_vec3 *normal)
{
	return (vec_sub(*vec, vec_mul(*normal, vec_dot(*vec, *normal) * 2.0)));
}

t_vec3	refract(const t_vec3 *uv, const t_vec3 *n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = vec_dot(vec_mul(*uv, -1.0), *n);
	if (cos_theta > 1.0)
		cos_theta = 1.0;
	r_out_perp = vec_mul(vec_add(*uv, vec_mul(*n, cos_theta)), etai_over_etat);
	r_out_parallel = vec_mul(*n,
			-1.0 * sqrt(fabs(1.0 - vec_len_sq(r_out_perp))));
	return (vec_add(r_out_perp, r_out_parallel));
}
