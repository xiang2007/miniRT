/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:22:52 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 11:09:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../../libft/libft.h"
#include <sys/time.h>
#include "../../includes/vec3.h"
#include <math.h>

static t_rng_state	*rng_state(void)
{
	static _Thread_local t_rng_state	rng;

	return (&rng);
}

static void	rng_seed(t_rng_state *rng)
{
	struct timeval	time;
	uint32_t		base;
	uint32_t		seed;

	gettimeofday(&time, NULL);
	base = (uint32_t)(uintptr_t)rng;
	seed = ((uint32_t)time.tv_sec ^ (base * 2654435761u));
	if (seed == 0)
		seed = 1;
	rng->seed.s = seed;
	rng->init = true;
}

double	random_double(double min, double max)
{
	t_rng_state	*rng;
	double		range;
	double		div;

	rng = rng_state();
	if (!rng->init)
		rng_seed(rng);
	range = max - min;
	div = UINT32_MAX / range;
	return (min + ((double) ft_xorshift32(&rng->seed) / div));
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
