/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 21:45:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/07 21:46:06 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/vec3.h"
#include "../includes/camera.h"
#include "../includes/objects.h"
#include "../includes/render.h"
#include "../includes/mlx_dat.h"
#include "../includes/parse.h"
#include "../mlx_Linux/mlx.h"
#include <stdlib.h>
#include <X11/keysym.h>

/**
 * @brief Setup ray tracer config data like aspect ratio, image height & width
 *
 * @param rt_dat pointer to the data struct
 */
void	rt_dat_init(t_rt *rt_dat)
{
	rt_dat->aspect_ratio = ASPECT_RATIO;
	rt_dat->img_w = WIDTH;
	rt_dat->img_h = WIDTH / rt_dat->aspect_ratio;
	rt_dat->max_bounce_depth = MAX_BOUNCE;
	rt_dat->old_max_bounce_depth = MAX_BOUNCE;
	rt_dat->samples_per_pixel = SPP;
	rt_dat->old_sampels_per_pixel = SPP;
	rt_dat->pixel_samples_scale = 1;
	rt_dat->old_pixel_samples_scale = 1;
	if (rt_dat->img_h < 1)
		rt_dat->img_h = 1;
	rt_dat->init = 0;
}

/**
 * @brief Frees the ray tracer data struct
 *
 * @param rt_dat pointer to the data struct
 */
void	rt_dat_free(t_rt *rt_dat)
{
	mlx_dat_free(rt_dat->mlx_dat);
	free(rt_dat);
}

void	setup_cam_init(t_setup_cam *s)
{
	s->center = create_vec3(0, 0, 0);
	s->fov = 0;
	s->norm_vector = create_vec3(0, 0, 0);
}
