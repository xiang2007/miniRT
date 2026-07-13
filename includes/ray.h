/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:15:34 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/05/12 00:18:10 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include <stdbool.h>

typedef struct s_ray
{
	t_point3	point;
	t_vec3		vec;
}				t_ray;

typedef struct s_hit_dat
{
	double		t;
	t_vec3	normal;
	t_vec3	point;
}	t_hit_dat;

t_ray	ray(t_point3 cam_center, t_vec3 ray_dir);
t_color	ray_color(t_ray *r, t_world *world);
t_vec3	ray_pos(t_ray *r, double t);

double	hit_sphere(t_sphere *sp, t_ray *r, double r_max, t_hit_dat *rec);
double	hit_plane(t_plane *p, t_ray *ray, double r_max, t_hit_dat *rec);

#endif
