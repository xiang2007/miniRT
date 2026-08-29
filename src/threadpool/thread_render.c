/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:18:45 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 00:48:52 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "threadpool.h"
#include "render.h"
#include "../../includes/minirt.h"
#include "../../includes/objects.h"
#include "../../includes/render.h"
#include "../../includes/mlx_dat.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void	render_tile(t_tile tile, t_rt *rt_dat)
{
	t_spp	spp;
	int		y;

	y = tile.start_y;
	spp.w = &rt_dat->world;
	spp.c = rt_dat->cam;
	spp.max_bounce_depth = rt_dat->max_bounce_depth;
	spp.spp = rt_dat->samples_per_pixel;
	spp.pss = 1.0 / rt_dat->samples_per_pixel;
	while (y < tile.end_y)
	{
		render_row(tile, spp, y, rt_dat);
		y++;
	}
}

static void	fill_tile(t_threads *td)
{
	td->tp->tiles[td->i].start_x = td->px;
	td->tp->tiles[td->i].start_y = td->py;
	td->tp->tiles[td->i].end_x = fmin(td->px + TILE_SIZE, td->rt->img_w);
	td->tp->tiles[td->i].end_y = fmin(td->py + TILE_SIZE, td->rt->img_h);
}

void	queue_tiles(t_threadpool *tp)
{
	t_threads	td;

	td.tp = tp;
	td.rt = tp->engine;
	td.rt->render_start = monotonic_seconds();
	td.i = 0;
	td.py = 0;
	while (td.py < td.rt->img_h)
	{
		td.px = 0;
		while (td.px < td.rt->img_w)
		{
			fill_tile(&td);
			td.i++;
			td.px += TILE_SIZE;
		}
		td.py += TILE_SIZE;
	}
	pthread_mutex_lock(&tp->queue_mutex);
	tp->tile_count = td.i;
	tp->tile_next = 0;
	pthread_cond_broadcast(&tp->queue_cond);
	pthread_mutex_unlock(&tp->queue_mutex);
}

double	monotonic_seconds(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

void	queue_render(t_rt *win)
{
	if (!win->tp || win->is_rendering)
		return ;
	win->is_rendering = true;
	mlx_swap_buffers(win->mlx_dat);
	ft_memset(win->mlx_dat->addr, 0,
			(size_t)win->mlx_dat->line_length * win->img_h);
	queue_tiles(win->tp);
}