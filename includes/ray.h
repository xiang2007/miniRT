/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:15:34 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/03 12:15:34 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray
{
	t_point3	point;
	t_vec3		vec;
}				t_ray;

t_ray	ray(t_point3 cam_center, t_vec3 ray_dir);
t_color	ray_color(t_ray *r, t_sphere *sp);

double		hit_sphere(t_sphere *sp, t_ray *r);

#endif
