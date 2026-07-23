/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/23 17:01:21 by wshou-xi         ###   ########.fr       */
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
	rt_dat->aspect_ratio = (double)16 / 9;
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

void	get_setup_cam(t_setup_cam *s, t_objects *objs)
{
	while (objs)
	{
		if (objs->type == OBJ_SETUP_CAM)
		{
			s->center = objs->cam_setup.center;
			s->norm_vector = objs->cam_setup.norm_vector;
			s->fov = objs->cam_setup.fov;
			return ;
		}
		objs = objs->next;
	}
}

int	reload_scene(t_rt *win)
{
	t_objects	*objs;
	t_setup_cam	s;
	t_world		world;

	world.objs = NULL;
	world.bvh_obj = NULL;
	world.bvh = NULL;
	setup_cam_init(&s);
	objs = parse("test_spheres_only.rt");
	if (!objs)
		return (1);
	get_setup_cam(&s, objs);
	parse_world(&world, objs);
	world_free(&win->world);
	win->world = world;
	cam_init(win->cam, win, &s);
	reset_res(win);
	render(win, win->cam, &win->world);
	return (0);
}

int	parse_and_render(t_rt *rt_dat)
{
	t_cam		*cam;
	t_objects	*objs;
	t_world		world;
	t_setup_cam	s;

	world.objs = NULL;
	world.bvh_obj = NULL;
	world.bvh = NULL;
	setup_cam_init(&s);
	objs = parse("test.rt");
	if (!objs)
		return (1);
	cam = malloc(sizeof(t_cam));
	get_setup_cam(&s, objs);
	parse_world(&world, objs);
	rt_dat->world = world;
	cam_init(cam, rt_dat, &s);
	rt_dat->cam = cam;
	render(rt_dat, rt_dat->cam, &rt_dat->world);
	return (0);
}

/**
 * @brief The orchestrator
 *
 * @param argc cli argument count
 * @param argv array of cli arguments
 * @return 1 on error, and 0 on normal exit
 */
int	main(int argc, char **argv)
{
	t_rt		rt_dat;

	(void)argc;
	(void)argv;
	rt_dat = (t_rt){0};
	rt_dat_init(&rt_dat);
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (0);
	if (parse_and_render(&rt_dat) == 1)
		return (1);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 2, 1L << 0, handle_key, &rt_dat);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 17, 1L << 17, close_all, &rt_dat);
	mlx_loop(rt_dat.mlx_dat->mlx);
	return (0);
}
