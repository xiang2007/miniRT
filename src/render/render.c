/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:07:24 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/02 21:07:24 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include "sphere.h"
#include "ray.h"
#include "objects.h"
#include "camera.h"
#include "color.h"
#include "mlx_dat.h"

#include <time.h>
#include <stdio.h>

void	render(t_rt *rt_dat, t_cam *c)
{
	clock_t	start, end;
	int		w;
	int		h;
	t_ray	r;
	t_color	cl;
	t_vec3	px_center;
	t_vec3	r_dir;
	t_sphere	sp;

	h = 0;
	w = 0;
	sp = sphere(create_vec3(0, 0, -1), 0.5);
	start = clock();
	while (h < rt_dat->img_h)
	{
		if (rt_dat->img_w == w) // not sure if it's faster or not yet
		{
			w = 0;
			h++;
		}
		px_center = vec_add(c->px00_loc, vec_add(vec_mul(c->px_delta_u, w), vec_mul(c->px_delta_v, h)));
		r_dir = vec_sub(px_center, c->cam_center);
		r = ray(c->cam_center, r_dir);
		cl = ray_color(&r, &sp);
		mlx_put_pixel(rt_dat->mlx_dat, w, h, color_get_hex(cl));
		w++;
	}
	end = clock();
	printf("Render took %f seconds to execute \n", ((double) (end - start)) / CLOCKS_PER_SEC);
	mlx_put_to_window(rt_dat->mlx_dat);
}