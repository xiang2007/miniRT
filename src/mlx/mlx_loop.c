/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 08:50:55 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_dat.h"
#include "threadpool.h"
#include "../../mlx_Linux/mlx.h"
#include <X11/keysym.h>

static void	apply_pending_key(t_threadpool *tp)
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

static void	update_render(t_threadpool *tp)
{
	pthread_mutex_lock(&tp->queue_mutex);
	if (threads_idle_locked(tp) == true && tp->tile_next >= tp->tile_count)
	{
		tp->engine->is_rendering = false;
		pthread_mutex_unlock(&tp->queue_mutex);
		tp->engine->render_time = monotonic_seconds()
			- tp->engine->render_start;
		mlx_clear_window(tp->engine->mlx_dat->mlx,
			tp->engine->mlx_dat->mlx_win);
		draw_controls(tp->engine);
		mlx_put_to_window(tp->engine->mlx_dat);
	}
	else if (tp->engine->samples_per_pixel == HQ_SAMPLING)
	{
		pthread_mutex_unlock(&tp->queue_mutex);
		mlx_put_to_window(tp->engine->mlx_dat);
	}
	else
		pthread_mutex_unlock(&tp->queue_mutex);
}

int	mlx_render_loop(void *param)
{
	t_threadpool	*tp;

	tp = param;
	if (tp->engine->key != 0)
		apply_pending_key(tp);
	else if (tp->engine->is_rendering == true)
		update_render(tp);
	return (0);
}

void	mlx_hook_init(t_rt *rt_dat)
{
	mlx_loop_hook(rt_dat->mlx_dat->mlx, mlx_render_loop, (void *)rt_dat->tp);
	mlx_hook(rt_dat->mlx_dat->mlx_win, 2, 1L << 0, handle_key, rt_dat);
	mlx_hook(rt_dat->mlx_dat->mlx_win, 17, 1L << 17, close_all, rt_dat);
	mlx_mouse_hook(rt_dat->mlx_dat->mlx_win, mouse_select, rt_dat);
}
