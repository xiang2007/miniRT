/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 09:19:47 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/color.h"
#include "minirt.h"

double	light_attenuation(t_light light, double distance)
{
	double	physical_intensity;
	double	attenuation;

	physical_intensity = light.brightness_ratio * LIGHT_WATTAGE;
	attenuation = physical_intensity / ((distance * distance) + 0.001);
	return (attenuation);
}

static double	material_fuzz(const t_material *mat)
{
	t_metal	*metal;

	if (mat && mat->scatter == metal_scatter)
	{
		metal = (t_metal *)mat;
		return (metal->fuzziness);
	}
	return (0.0);
}

t_color	material_albedo(const t_material *mat, t_color fallback)
{
	t_lambertian	*lam;

	if (!mat)
		return (fallback);
	if (mat->scatter == dielectric_scatter)
		return (create_color(1.0, 1.0, 1.0));
	lam = (t_lambertian *)mat;
	if (mat->scatter == lambertian_scatter && lam->checker_size > 0.0)
		return (fallback);
	return (lam->albedo);
}

void	lightning_helper(t_lightning *l, t_hit_dat *rec, t_ray *r,
		t_light light)
{
	double	fuzz;

	fuzz = material_fuzz(rec->mat);
	l->brightness = fmax(vec3_dot(rec->normal, l->light_dir), 0.0);
	l->brightness *= light_attenuation(light, l->light_distance);
	l->light_in = vec3_mul(l->light_dir, -1.0);
	l->reflected = reflect(&l->light_in, &rec->normal);
	if (fuzz > 0.0)
		l->reflected = vec3_add(l->reflected, vec3_mul(rand_unit_vec3(), fuzz));
	l->reflected = unit_vec3(l->reflected);
	l->view_dir = unit_vec3(vec3_mul(r->vec, -1.0));
	if (rec->mat && rec->mat->scatter == dielectric_scatter)
		l->specular = pow(fmax(1.0 - vec3_dot(rec->normal, l->view_dir), 0.0),
				5.0);
	else if (rec->mat && rec->mat->specular_strength > 0.0
		&& rec->mat->shininess > 0.0)
		l->specular = rec->mat->specular_strength * pow(fmax(
					vec3_dot(l->view_dir, l->reflected), 0.0),
				rec->mat->shininess);
	else
		l->specular = 0.0;
	l->specular *= light_attenuation(light, l->light_distance);
}
