/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:07:24 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 11:24:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"
#include "color.h"
#include "mlx_dat.h"
#include "render.h"

static t_color	spp_loop(t_spp spp, int n)
{
	t_color	cl;

	cl = create_color(0, 0, 0);
	spp.offset = vec3_rand(-0.5, 0.5);
	spp.offset.z = 0.0;
	spp.px_sample = vec3_add(
			spp.c->px00_loc,
			vec3_add(
				vec3_mul(spp.c->px_delta_u, n + spp.offset.x),
				vec3_mul(spp.c->px_delta_v, spp.h + spp.offset.y)));
	spp.r_dir = vec3_sub(spp.px_sample, spp.c->cam_center);
	spp.r = ray(spp.c->cam_center, spp.r_dir);
	cl = ray_color(&spp.r, spp.max_bounce_depth, spp.w);
	return (cl);
}

void	render_row(t_tile tile, t_spp spp, int y, t_rt *rt_dat)
{
	t_color	cl;
	int		x;
	int		sample;

	x = tile.start_x;
	spp.h = y;
	while (x < tile.end_x)
	{
		sample = 0;
		cl = create_color(0, 0, 0);
		while (sample < spp.spp)
		{
			cl = color_add(cl, spp_loop(spp, x));
			sample++;
		}
		cl.r = linear_to_gamma(spp.pss * cl.r / (1.0 + spp.pss * cl.r));
		cl.g = linear_to_gamma(spp.pss * cl.g / (1.0 + spp.pss * cl.g));
		cl.b = linear_to_gamma(spp.pss * cl.b / (1.0 + spp.pss * cl.b));
		mlx_put_pixel(rt_dat->mlx_dat, x, y, color_get_hex(cl));
		x++;
	}
}
