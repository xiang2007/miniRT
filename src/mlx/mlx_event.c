/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:39:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/31 13:50:53 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/aabb.h"
#include <X11/keysym.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

void	rebuild_world_bvh(t_world *world)
{
	t_objects	**objects;
	t_bvh		*root;
	int			count;

	count = obj_bvh_count(world->objs);
	objects = obj2arr(world->objs);
	if (!objects || count <= 0)
		return (free(objects));
	root = build_bvh(objects, 0, count);
	if (!root)
		return (free(objects));
	free_bvh(world->bvh);
	free(world->bvh_obj);
	world->bvh = root;
	world->bvh_obj = objects;
}

/**
 * @brief Frees all obj structs in world
 *
 * @param world world struct
 */
void	world_free(t_world *world)
{
	t_objects	*tmp;

	if (!world)
		return ;
	free_bvh(world->bvh);
	free(world->bvh_obj);
	world->bvh = NULL;
	world->bvh_obj = NULL;
	while (world->objs)
	{
		tmp = world->objs;
		world->objs = world->objs->next;
		free_object_material(tmp);
		free(tmp);
	}
}

static void	dispatch_key(int key, t_rt *win)
{
	if (key == XK_r)
		reload_scene(win);
	if (key >= XK_0 && key <= XK_9)
		win->sel_obj = select_object(key, &win->world);
	if ((key >= XK_Left && key <= XK_Down && win->sel_obj)
		|| ((key == XK_minus || key == XK_equal) && win->sel_obj))
		handle_move_object(key, win);
	if (key == XK_w || key == XK_s || key == XK_a
		|| key == XK_d || key == XK_q || key == XK_e)
		handle_camera_move(key, win);
	if (key == XK_z)
		handle_key_z(win);
	if (key == XK_bracketleft || key == XK_bracketright
		|| key == XK_semicolon || key == XK_apostrophe)
	{
		if (win->sel_obj)
			handle_rotate_object(key, win);
		else
			handle_camera_rotate(key, win);
	}
	if (key == XK_h)
	{
		win->show_controls = !win->show_controls;
		draw_controls(win);
	}
	if (key == XK_c)
		handle_toggle_checker(win);
}

/**
 * @brief Checks if a key pressed
 * - If Escape Key is pressed, all malloced data are freed and exit with 0
 *
 * @param key key pressed
 * @param win window data
 * @return returns 0
 */
int	handle_key(int key, t_rt *win)
{
	if (key == XK_Escape)
	{
		pthread_mutex_lock(&win->tp->queue_mutex);
		win->needs_rerender = false;
		win->is_rendering = false;
		win->abort_flag = true;
		pthread_mutex_unlock(&win->tp->queue_mutex);
		pthread_cond_broadcast(&win->tp->queue_cond);
		pthread_mutex_lock(&win->tp->queue_mutex);
		while (!threads_idle_locked(win->tp))
			pthread_cond_wait(&win->tp->done_cond, &win->tp->queue_mutex);
		pthread_mutex_unlock(&win->tp->queue_mutex);
		threadpool_destroy(win->tp);
		world_free(&win->world);
		mlx_dat_free(win->mlx_dat);
		free(win->cam);
		exit(0);
	}
	else
	{
		if (win->is_rendering)
		{
			win->pending_key = key;
			win->has_pending = true;
			return (0);
		}
		dispatch_key(key, win);
	}
	return (0);
}

/**
 * @brief Frees all malloced data
 *
 * @param win window data
 * @return returns nothingv
 */
int	close_all(t_rt *win)
{
	threadpool_destroy(win->tp);
	world_free(&win->world);
	mlx_dat_free(win->mlx_dat);
	exit(0);
}
