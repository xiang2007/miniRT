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

#include "vec3.h"
typedef struct s_ray		t_ray;
typedef struct s_hit_dat	t_hit_dat;

typedef struct s_scatter_args
{
	const struct s_material	*self;
	const t_ray				*in;
	const t_hit_dat			*rec;
	t_color					*attenuation;
	t_ray					*scattered;
}							t_scatter_args;

typedef bool				t_scatter_fn(t_scatter_args *args);

typedef struct s_material
{
	t_scatter_fn	*scatter;
}				t_material;

typedef struct s_lambertian
{
	t_material	base;
	t_color		albedo;
	t_color		checker_color;
	double		checker_size;
}				t_lambertian;

typedef struct s_metal
{
	t_material	base;
	t_color		albedo;
	double		fuzziness;
}				t_metal;

typedef struct s_dielectric
{
	t_material	base;
	double		refractive_index;
}				t_dielectric;

typedef struct s_dielectric_scatter
{
	t_dielectric	*die;
	t_vec3			unit_direction;
	t_vec3			direction;
	double			ri;
	double			cos_theta;
	double			sin_theta;
	bool			cannot_refract;
}					t_dielectric_scatter;

bool		lambertian_scatter(t_scatter_args *args);
t_material	*create_lambertian(t_color cl);

bool		metal_scatter(t_scatter_args *args);
t_material	*create_metal(const t_color cl, const double fuzz);

bool		dielectric_scatter(t_scatter_args *args);
t_material	*create_dielectric(const double refraction_index);

#endif
