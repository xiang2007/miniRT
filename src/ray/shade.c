/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 20:55:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "../../includes/ray.h"
#include "../../includes/color.h"
#include "../../includes/material.h"
#include "minirt.h"
#include "vec3.h"

t_color	scatter_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth)
{
	t_scatter_args	args;
	t_color			bounced;
	t_color			light_hits;

	args = (t_scatter_args){0};
	args.self = rec->mat;
	args.in = r;
	args.rec = rec;
	args.attenuation = &(t_color){0};
	args.scattered = &(t_ray){0};
	if (!rec->mat->scatter(&args))
		return (create_color(0, 0, 0));
	bounced = color_mul(*args.attenuation,
			ray_color(args.scattered, depth - 1, w));
	light_hits = recursive_light_hits((t_recurse_args){rec, w, args.scattered,
			rec->mat->cone_fuzz, *args.attenuation});
	return (color_add(bounced, light_hits));
}
