/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:58:35 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 18:58:58 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/material.h"
#include <stdlib.h>
#include "color.h"

t_material	*create_lambertian(const t_color cl)
{
	t_lambertian	*lam;

	lam = malloc(sizeof(t_lambertian));
	if (!lam)
		return (NULL);
	lam->base.scatter = &lambertian_scatter;
	lam->albedo = cl;
	lam->checker_color = create_color(0, 0, 0);
	lam->checker_size = 0.0;
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

t_material	*create_dielectric(const double refraction_index)
{
	t_dielectric	*die;

	die = malloc(sizeof(t_dielectric));
	if (!die)
		return (NULL);
	die->base.scatter = &dielectric_scatter;
	die->refractive_index = refraction_index;
	return ((t_material *)die);
}
