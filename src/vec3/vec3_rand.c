/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:22:52 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/07 17:22:52 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "../../libft/libft.h"
#include <sys/time.h>
#include "../../includes/vec3.h"

static	double	random_double(double min, double max)
{
	struct timeval		time;
	static t_xorshift32	seed;
	double				range;
	double				div;

	if (seed.s == 0)
		gettimeofday(&time, NULL);
	seed.s = time.tv_usec;
	range = max - min;
	div = DBL_MAX / range;
	return (min + (ft_xorshift32(&seed) / div));
}

t_vec3	vec3_rand(double min, double max)
{
	t_vec3	vec3;

	vec3.x = random_double(min, max);
	vec3.y = random_double(min, max);
	vec3.z = random_double(min, max);
	return (vec3);
}