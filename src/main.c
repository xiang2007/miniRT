/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/07 21:46:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/camera.h"
#include "../includes/objects.h"
#include "../includes/render.h"
#include "../includes/mlx_dat.h"
#include "../includes/parse.h"
#include "../mlx_Linux/mlx.h"
#include <stdlib.h>
#include <X11/keysym.h>

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
	objs = parse("test_cornell_box.rt");
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
	objs = parse("test_cornell_box.rt");
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
