/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:22:52 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/13 17:18:16 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "../../libft/libft.h"
#include <sys/time.h>
#include "../../includes/vec3.h"
#include <math.h>
#include <stdio.h>
static	double	random_double(double min, double max)
{
	struct timeval		time;
	static t_xorshift32	seed;
	double				range;
	double				div;

	if (seed.s == 0)
	{
		gettimeofday(&time, NULL);
		seed.s = time.tv_sec;
	}
	range = max - min;
	div = UINT32_MAX / range;
	return (min + ((double) ft_xorshift32(&seed) / div));
}

t_vec3	vec3_rand(double min, double max)
{
	t_vec3	vec3;

	vec3.x = random_double(min, max);
	vec3.y = random_double(min, max);
	vec3.z = random_double(min, max);
	return (vec3);
}

t_vec3	rand_unit_vec3(void)
{
	t_vec3	p;
	double	lensq;

	while (1)
	{
		p = vec3_rand(-1.0, 1.0);
		lensq = vec_len_sq(p);
		if (1e-160 < lensq && lensq <= 1)
			return (vec_div(p, sqrt(lensq)));
	}
}

t_vec3	rand_on_hemi(const t_vec3 *normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = rand_unit_vec3();
	if (vec_dot(on_unit_sphere, *normal) > 0.0)
		return (on_unit_sphere);
	else
		return (vec_mul(on_unit_sphere, -1.0));
}