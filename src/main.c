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

#include "../includes/camera.h"
#include "../includes/minirt.h"
#include "../includes/objects.h"
#include "../includes/mlx_dat.h"
#include "../includes/parse.h"
#include "../mlx_Linux/mlx.h"
#include "X11/keysym.h"
#include <pthread.h>
#include <stdlib.h>
#include "libft.h"
#include "threadpool.h"

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

int	parse_and_render(t_rt *rt_dat, t_threadpool *tp)
{
	t_cam		*cam;
	t_objects	*objs;
	t_world		world;
	t_setup_cam	s;

	world.objs = NULL;
	world.bvh_obj = NULL;
	world.bvh = NULL;
	setup_cam_init(&s);
	objs = parse(rt_dat->test_file);
	if (!objs)
		return (1);
	cam = malloc(sizeof(t_cam));
	get_setup_cam(&s, objs);
	parse_world(&world, &objs);
	rt_dat->world = world;
	cam_init(cam, rt_dat, &s);
	rt_dat->cam = cam;
	if (rt_dat->is_rendering == false)
	{
		rt_dat->is_rendering = true;
		queue_tiles(tp);
	}
	return (0);
}

void	keymap(int key, t_rt *dat)
{
	if ((key >= XK_Left && key <= XK_Down)|| key == XK_minus || key == XK_equal)
	{
		dat->sel_obj->translate(dat->sel_obj, key);
		if (dat->sel_obj->type == OBJ_SPHERE || dat->sel_obj->type == OBJ_CYLINDER
				|| dat->sel_obj->type == OBJ_CONE)
			rebuild_world_bvh(&dat->world);
	}
	else if (key == XK_bracketleft || key == XK_bracketright || key == XK_semicolon || key == XK_apostrophe)
	{
		if (dat->sel_obj)
			handle_rotate_object(key, dat);
		else
			handle_camera_rotate(key, dat);
	}
	else if (key == XK_w || key == XK_s || key == XK_a || key == XK_d || key == XK_q || key == XK_e)
		camera_move(key, dat);
	else if (key == XK_c)
		toggle_checker(dat->sel_obj);
	if (key == XK_z)
	{
		dat->max_bounce_depth = 50;
		dat->samples_per_pixel = 100;
	}
	else
		reset_res(dat);
}

int	mlx_render_loop(void *param)
{
	t_threadpool	*tp;
	
	tp = param;
	if (tp->engine->key != 0)
	{
		pthread_mutex_lock(&tp->queue_mutex);
		tp->engine->abort_flag = true;
		tp->tile_next = tp->tile_count;
		pthread_mutex_unlock(&tp->queue_mutex);
		
		pthread_cond_broadcast(&tp->queue_cond);
		
		pthread_mutex_lock(&tp->queue_mutex);
		while (!threads_idle_locked(tp))
			pthread_cond_wait(&tp->done_cond, &tp->queue_mutex);
		pthread_mutex_unlock(&tp->queue_mutex);
		
		keymap(tp->engine->key, tp->engine);
		
		tp->engine->is_rendering = false;
		tp->engine->abort_flag = false;
		tp->engine->key = 0;
		queue_render(tp->engine);
	}
	else if (tp->engine->is_rendering == true)
	{
		pthread_mutex_lock(&tp->queue_mutex);
		if (threads_idle_locked(tp) == true && tp->tile_next >= tp->tile_count)
		{
			tp->engine->is_rendering = false;
			pthread_mutex_unlock(&tp->queue_mutex);
			tp->engine->render_time = monotonic_seconds()
				- tp->engine->render_start;
			printf("Render took %.2f s\n", tp->engine->render_time);
			mlx_clear_window(tp->engine->mlx_dat->mlx, tp->engine->mlx_dat->mlx_win);
			draw_controls(tp->engine);
			mlx_put_to_window(tp->engine->mlx_dat);
		}
		else
		{
			pthread_mutex_unlock(&tp->queue_mutex);
			mlx_put_to_window(tp->engine->mlx_dat);
		}
	}
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
	t_threadpool	*tp;
	t_rt			rt_dat;

	if (argc != 2)
		return (1);
	rt_dat = (t_rt){0};
	rt_dat_init(&rt_dat);
	rt_dat.test_file = argv[1];
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (0);
	tp = threadpool_create(&rt_dat, 12);
	if (!tp)
		return (1);
	rt_dat.tp = tp;
	if (parse_and_render(&rt_dat, tp) == 1)
		return (1);
	mlx_loop_hook(rt_dat.mlx_dat->mlx, mlx_render_loop, (void *)tp);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 2, 1L << 0, handle_key, &rt_dat);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 17, 1L << 17, close_all, &rt_dat);
	mlx_mouse_hook(rt_dat.mlx_dat->mlx_win, mouse_select, &rt_dat);
	mlx_loop(rt_dat.mlx_dat->mlx);
	return (0);
}
