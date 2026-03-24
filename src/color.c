/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:32:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 15:20:41 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	create_color(double r, double g, double b)
{
	t_color	res;

	res.r = r;
	res.b = b;
	res.g = g;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	add_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	mult_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	mult_color_n(t_color c, double n)
{
	t_color	res;

	res.r = c.r * n;
	res.g = c.g * n;
	res.b = c.b * n;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	ray_color(t_ray r, t_sphere sp)
{
	double	t;
	double	a;
	t_color	res;
	t_vec3	u_dir;
	t_vec3	n;

	t = hit_sphere(create_vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		n = unit_vec(sub_vec(ray_pos(r, t), sp.point));
		return (mult_color_n(create_color(n.x + 1, n.y + 1, n.z + 1), 0.5));
	}
	u_dir = unit_vec(r.vec);
	a = 0.5 * (u_dir.y + 1);
	res = add_color(mult_color_n(create_color(1, 1, 1), (1 - a)),
				mult_color_n(create_color(0.5, 0.7, 1), a));
	return (res);
}
