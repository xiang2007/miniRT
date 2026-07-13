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
	t_vec3	px_center;
	t_vec3	r_dir;
	int		max_bounce_depth; // Maximum number of ray bounces into scene

	h = 0;
	max_bounce_depth = 10;
	start = clock();
	while (h < rt_dat->img_h)
	{
		w = 0;
		while (w < rt_dat->img_w)
		{
			px_center = vec_add(c->px00_loc, vec_add(vec_mul(c->px_delta_u, w), vec_mul(c->px_delta_v, h)));
			r_dir = vec_sub(px_center, c->cam_center);
			r = ray(c->cam_center, r_dir);
			cl = ray_color(&r, max_bounce_depth, world);
			mlx_put_pixel(rt_dat->mlx_dat, w, h, color_get_hex(cl));
			w++;
		}
		h++;
	}
	end = clock();
	printf("Render took %f seconds to execute \n", ((double) (end - start)) / CLOCKS_PER_SEC);
	mlx_put_to_window(rt_dat->mlx_dat);
}
