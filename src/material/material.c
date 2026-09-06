/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 01:53:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 11:17:05 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/material.h"
#include <math.h>
#include "../../includes/ray.h"
#include "../../includes/color.h"

bool	lambertian_scatter(t_scatter_args *args)
{
	t_vec3			scatter_direction;
	t_lambertian	*lam;

	scatter_direction = vec3_add(args->rec->normal, rand_unit_vec3());
	if (near_zero(&scatter_direction))
		scatter_direction = args->rec->normal;
	*args->scattered = ray(args->rec->point, scatter_direction);
	lam = (t_lambertian *)args->self;
	*args->attenuation = lam->albedo;
	return (true);
}

bool	metal_scatter(t_scatter_args *args)
{
	t_vec3	reflected;
	t_metal	*metal;

	reflected = reflect(&args->in->vec, &args->rec->normal);
	metal = (t_metal *)args->self;
	reflected = vec3_add(unit_vec3(reflected),
			vec3_mul(rand_unit_vec3(), metal->fuzziness));
	*args->scattered = ray(args->rec->point, reflected);
	*args->attenuation = metal->albedo;
	return (vec3_dot(args->scattered->vec, args->rec->normal));
}

static double	reflectance(double cosine, double refraction_index)
{
	double	r0;

	r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

static void	dielectric_pick_direction(t_scatter_args *args,
				t_dielectric_scatter *dat)
{
	dat->unit_direction = unit_vec3(args->in->vec);
	dat->cos_theta = vec3_dot(vec3_mul(dat->unit_direction, -1.0),
			args->rec->normal);
	if (dat->cos_theta > 1.0)
		dat->cos_theta = 1.0;
	dat->sin_theta = sqrt(1.0 - dat->cos_theta * dat->cos_theta);
	dat->cannot_refract = dat->ri * dat->sin_theta > 1.0;
	if (dat->cannot_refract || reflectance(dat->cos_theta, dat->ri)
		> random_double(0.0, 1.0))
		dat->direction = reflect(&dat->unit_direction,
				&args->rec->normal);
	else
		dat->direction = refract(&dat->unit_direction,
				&args->rec->normal, dat->ri);
}

bool	dielectric_scatter(t_scatter_args *args)
{
	t_dielectric_scatter	dat;

	dat = (t_dielectric_scatter){0};
	dat.die = (t_dielectric *)args->self;
	*args->attenuation = create_color(1.0, 1.0, 1.0);
	dat.ri = dat.die->refractive_index;
	if (dat.ri <= 0.0)
		dat.ri = 1.5;
	if (args->rec->front_face)
		dat.ri = 1.0 / dat.ri;
	dielectric_pick_direction(args, &dat);
	*args->scattered = ray(vec3_add(args->rec->point,
				vec3_mul(dat.direction, 0.001)), dat.direction);
	return (true);
}
