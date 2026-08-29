/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:15:34 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 11:26:46 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "objects.h"
# include <stdbool.h>

typedef struct s_ray
{
	t_point3	point;
	t_vec3		vec;
}				t_ray;

typedef struct s_hit_dat
{
	double		t;
	t_vec3		normal;
	t_vec3		point;
	t_color		color;
	bool		front_face;
	t_material	*mat;
	t_objects	*hit_obj;
}	t_hit_dat;

typedef struct s_cylinder_args
{
	t_cylinder	*cy;
	t_ray		*ray;
	double		r_max;
	t_hit_dat	*rec;
}				t_cylinder_args;

typedef struct s_hit_sphere
{
	t_vec3	ori_center;
	t_vec3	outward_normal;
	double	a;
	double	h;
	double	c;
	double	d;
	double	root;
}			t_hit_sphere;

typedef struct s_lightning
{
	t_ray		shadow_ray;
	t_hit_dat	shadow_rec;
	t_vec3		light_dir;
	t_vec3		shadow_ori;
	t_vec3		light_in;
	t_vec3		reflected;
	t_vec3		view_dir;
	t_color		result;
	double		light_distance;
	double		brightness;
	double		specular;
	double		falloff;
}				t_lightning;

typedef struct s_recurse_l_hit
{
	t_objects	*obj;
	t_color		result;
	t_vec3		out_dir;
	t_vec3		light_dir;
	t_ray		shadow_ray;
	double		alignment;
	double		accept_cos;
	double		intensity;
	double		distance;
}				t_recurse_l_hit;

typedef struct s_recurse_args
{
	t_hit_dat	*rec;
	t_world		*world;
	const t_ray	*outgoing;
	double		fuzz;
	t_color		tint;
}				t_recurse_args;

typedef struct s_metal_shade
{
	t_metal	*metal;
	t_vec3	reflected;
	t_vec3	fuzzy;
	t_ray	scattered;
	t_color	bounced;
	t_color	light_hits;
	double	fuzz;
}				t_metal_shade;

bool	hit_list(t_ray *r, t_world *world, t_hit_dat *rec);
t_ray	ray(t_point3 cam_center, t_vec3 ray_dir);
t_color	ray_color(t_ray *r, int bounce_depth, t_world *world);
t_vec3	ray_pos(t_ray *r, double t);
double	get_ray_vec_n(t_ray *ray, int n);
double	get_ray_point_n(t_ray *ray, int n);
t_vec3	ray_pos(t_ray *r, double t);

double	hit_sphere(t_sphere *sp, t_ray *r, double r_max, t_hit_dat *rec);
double	hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec);
double	hit_cylinder(t_cylinder *cy, t_ray *ray, double r_max, t_hit_dat *rec);
double	hit_cap(t_cylinder_args *args, const t_vec3 *center,
			const t_vec3 *normal);
void	hit_cylinder_tube(t_cylinder_hit *hit, t_cylinder_args *args);
void	hit_cylinder_tube2(t_cylinder_hit *hit, t_cylinder_args *args);
void	hit_cylinder_caps(t_cylinder_hit *hit, t_cylinder_args *args);

t_color	lightning(t_hit_dat *rec, t_world *w, t_ray *r, t_light light);
double	light_attenuation(t_light light, double distance);
t_color	ambient_light(t_world *w);
bool	shadow_hit(t_world *w, t_ray *ray, double t_max, t_objects *skip);
t_color	recursive_light_hits(t_recurse_args args);
t_color	metal_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth);
t_color	dielectric_shade(t_hit_dat *rec, t_world *w, t_ray *r, int depth);
bool	material_is_transparent(t_objects *o);
bool	shadow_hit(t_world *w, t_ray *ray, double t_max, t_objects *skip);

#endif
