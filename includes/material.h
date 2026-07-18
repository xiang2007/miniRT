/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 01:54:04 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/15 01:54:04 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct s_ray t_ray;
typedef struct s_hit_dat t_hit_dat;

typedef struct s_material {
	bool (*scatter)(const struct s_material *self, const t_ray *in, const t_hit_dat *rec, t_vec3 *attenuation, t_ray *scattered);
} t_material;

typedef struct s_lambertian
{
	t_material	base;
	t_color		albedo;
}	t_lambertian;

typedef struct s_metal {
	t_material	base;            // Must be first!
	t_color		albedo;
	double		fuzziness;       // ONLY metal has this!
} t_metal;

typedef struct s_glass {
	t_material	base;            // Must be first! Holds the scatter pointer.
	double		refractive_index; // ONLY glass has this!
} t_glass;

bool	lambertian_scatter(const struct s_material *self, const t_ray *in, const t_hit_dat *rec, t_color *attenuation, t_ray *scattered);
t_material	*create_lambertian(t_color cl);

bool	metal_scatter(const struct s_material *self, const t_ray *in, const t_hit_dat *rec, t_color *attenuation, t_ray *scattered);
t_material	*create_metal(const t_color cl, const double fuzz);

#endif
