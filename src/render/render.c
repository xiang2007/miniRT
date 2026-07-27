/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:07:24 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/28 07:39:47 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/vec3.h"
#include "../../includes/objects.h"
#include "../../includes/ray.h"
#include "../../includes/camera.h"
#include "../../includes/color.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/render.h"

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

static t_color	spp_loop(t_spp spp, int n)
{
	t_color	cl;

	cl = create_color(0, 0, 0);
	spp.offset = vec3_rand(-0.5, 0.5);
	spp.offset.z = 0.0;
	spp.px_sample = vec_add(
			spp.c->px00_loc,
			vec_add(
				vec_mul(spp.c->px_delta_u, n + spp.offset.x),
				vec_mul(spp.c->px_delta_v, spp.h + spp.offset.y)));
	spp.r_dir = vec_sub(spp.px_sample, spp.c->cam_center);
	spp.r = ray(spp.c->cam_center, spp.r_dir);
	cl = ray_color(&spp.r, spp.max_bounce_depth, spp.w);
	return (cl);
}

static void	render_row(t_rt *rt_dat, t_spp spp, int h)
{
	t_color	cl;
	int		w;
	int		sample;

	w = 0;
	spp.h = h;
	while (w < rt_dat->img_w)
	{
		sample = 0;
		cl = create_color(0, 0, 0);
		while (sample < spp.spp)
		{
			cl = color_add(cl, spp_loop(spp, w));
			sample++;
		}
		cl.r = clamp(linear_to_gamma(spp.pss * cl.r), 0.000, 0.999);
		cl.g = clamp(linear_to_gamma(spp.pss * cl.g), 0.000, 0.999);
		cl.b = clamp(linear_to_gamma(spp.pss * cl.b), 0.000, 0.999);
		mlx_put_pixel(rt_dat->mlx_dat, w, h, color_get_hex(cl));
		w++;
	}
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
	clock_t	start;
	clock_t	end;
	int		h;
	t_spp	spp;

	h = 0;
	spp.w = world;
	spp.c = c;
	spp.max_bounce_depth = rt_dat->max_bounce_depth;
	spp.spp = rt_dat->samples_per_pixel;
	spp.pss = 1.0 / rt_dat->samples_per_pixel;
	start = clock();
	while (h < rt_dat->img_h)
	{
		render_row(rt_dat, spp, h);
		h++;
	}
	end = clock();
	printf("Render took %f seconds to execute \n",
		((double)(end - start)) / CLOCKS_PER_SEC);
	mlx_put_to_window(rt_dat->mlx_dat);
}
