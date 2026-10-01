/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 08:50:55 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "objects.h"
#include "mlx_dat.h"
#include "parse.h"
#include "mlx.h"
#include "X11/keysym.h"
#include <pthread.h>
#include <stdlib.h>
#include "threadpool.h"

/**
 * @brief Setup ray tracer config data like aspect ratio, image height & width
 *
 * @param rt_dat pointer to the data struct
 */
static void	rt_dat_init(t_rt *rt_dat)
{
	rt_dat->img_w = WIDTH;
	rt_dat->img_h = WIDTH / ASPECT_RATIO;
	rt_dat->max_bounce_depth = LQ_BOUNCE_DEPTH;
	rt_dat->samples_per_pixel = LQ_SAMPLING;
	if (rt_dat->img_h < 1)
		rt_dat->img_h = 1;
	rt_dat->sel_light_id = -1;
	rt_dat->sel_object_id = -1;
	rt_dat->is_rendering = false;
}

static int	rt_dat_free(t_rt *rt_dat)
{
	world_free(&rt_dat->world);
	free(rt_dat->cam);
	return (1);
}

static int	parse_and_cam_init(t_rt *rt_dat, char *scene_file)
{
	t_cam		*cam;
	t_objects	*objs;
	t_setup_cam	s;

	s = (t_setup_cam){0};
	objs = parse(scene_file);
	if (!objs)
		return (1);
	cam = malloc(sizeof(t_cam));
	if (!cam)
	{
		parse_free_objects(objs);
		return (1);
	}
	get_setup_cam(&s, objs);
	cam_init(cam, rt_dat, &s);
	rt_dat->cam = cam;
	parse_world(&rt_dat->world, &objs);
	return (0);
}

/**
 * @brief The orchestrator
 *
 */
int	main(int argc, char **argv)
{
	t_rt			rt_dat;

	if (argc != 2)
		return (1);
	rt_dat = (t_rt){0};
	rt_dat_init(&rt_dat);
	if (parse_and_cam_init(&rt_dat, argv[1]) == 1)
		return (1);
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (rt_dat_free(&rt_dat));
	rt_dat.tp = threadpool_create(&rt_dat, 12);
	if (!rt_dat.tp)
	{
		rt_dat_free(&rt_dat);
		return (mlx_dat_free(rt_dat.mlx_dat));
	}
	if (rt_dat.is_rendering == false)
	{
		rt_dat.is_rendering = true;
		queue_tiles(rt_dat.tp);
	}
	mlx_hook_init(&rt_dat);
	mlx_loop(rt_dat.mlx_dat->mlx);
	return (0);
}
