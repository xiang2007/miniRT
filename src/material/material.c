/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 01:53:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/15 01:53:54 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"
#include "../../includes/vec3.h"
#include "../../includes/material.h"
#include "../../includes/ray.h"
#include <stdlib.h>
#include <stdbool.h>

bool	lambertian_scatter(const struct s_material *self, const t_ray *in, const t_hit_dat *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3	scatter_direction;
	t_lambertian	*lam;

	(void)in;
	scatter_direction = vec_add(rec->normal, rand_unit_vec3());
	if (near_zero(&scatter_direction))
		scatter_direction = rec->normal;
	*scattered = ray(rec->point, scatter_direction);
	lam = (t_lambertian *) self;
	*attenuation = lam->albedo;
	return (true);
}

bool	metal_scatter(const struct s_material *self, const t_ray *in, const t_hit_dat *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3	reflected;
	t_metal	*metal;

	reflected = reflect(&in->vec, &rec->normal);
	metal = (t_metal *) self;
	reflected = vec_add(unit_vec(reflected), vec_mul(rand_unit_vec3(), metal->fuzziness));
	*scattered = ray(rec->point, reflected);
	*attenuation = metal->albedo;
	return (vec_dot(scattered->vec, rec->normal));
}

t_material	*create_lambertian(const t_color cl)
{
	t_lambertian	*lam;

	lam = malloc(sizeof(t_lambertian));
	if (!lam)
		return (NULL);
	lam->base.scatter = &lambertian_scatter;
	lam->albedo = cl;
	return ((t_material *)lam);
}

t_material	*create_metal(const t_color cl, const double fuzz)
{
	t_metal	*metal;

	metal = malloc(sizeof(t_metal));
	if (!metal)
		return (NULL);
	metal->base.scatter = &metal_scatter;
	metal->albedo = cl;
	metal->fuzziness = fuzz;
	return ((t_material *)metal);
}