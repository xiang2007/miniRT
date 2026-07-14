/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:07:24 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/06/11 02:56:54 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/vec3.h"
#include "../../includes/objects.h"
#include "../../includes/ray.h"
#include "../../includes/camera.h"
#include "../../includes/color.h"
#include "../../includes/mlx_dat.h"

#include <time.h>
#include <stdio.h>

double	clamp(double cl, double min, double max)
{
	if (cl < min)
		return (min);
	if (cl > max)
		return (max);
	return (cl);
}

/**
 * @brief Main component where rendering happens TODO: more info here
 *
 * @param rt_dat the ray tracer struct
 * @param c the camera struct
 * @param world the world struct
 */
void	render(t_rt *rt_dat, t_cam *c, t_world *world)
{
	clock_t	start, end;
	int		w;
	int		h;
	t_ray	r;
	t_color	cl;
	t_vec3	px_sample;
	t_vec3	r_dir;
	int		max_bounce_depth; // Maximum number of ray bounces into scene
	int		samples_per_pixel;   // Count of random samples for each pixel
	double	pixel_samples_scale; // Color scale factor for a sum of pixel samples
	int		sample;
	t_vec3	offset;

	h = 0;
	max_bounce_depth = 10;
	samples_per_pixel = 10;
	pixel_samples_scale = 1.0 / samples_per_pixel;
	start = clock();
	while (h < rt_dat->img_h)
	{
		w = 0;
		while (w < rt_dat->img_w)
		{
			sample = 0;
			cl.r = 0;
			cl.g = 0;
			cl.b = 0;
			while (sample < samples_per_pixel)
			{
				offset = vec3_rand(-0.5, +0.5);
				offset.z = 0.0;
				px_sample = vec_add(c->px00_loc, vec_add(vec_mul(c->px_delta_u, w + offset.x), vec_mul(c->px_delta_v, h + offset.y)));
				r_dir = vec_sub(px_sample, c->cam_center);
				r = ray(c->cam_center, r_dir);
				cl = color_add(cl, ray_color(&r, max_bounce_depth, world));
				sample++;
			}
			cl.r = clamp(linear_to_gamma(pixel_samples_scale * cl.r), 0.000, 0.999);
			cl.g = clamp(linear_to_gamma(pixel_samples_scale * cl.g), 0.000, 0.999);
			cl.b = clamp(linear_to_gamma(pixel_samples_scale * cl.b), 0.000, 0.999);
			mlx_put_pixel(rt_dat->mlx_dat, w, h, color_get_hex(cl));
			w++;
		}
		h++;
	}
	end = clock();
	printf("Render took %f seconds to execute \n", ((double) (end - start)) / CLOCKS_PER_SEC);
	mlx_put_to_window(rt_dat->mlx_dat);
}
