/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:18:45 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/14 19:18:45 by ydylan-k         ###   ########.fr       */
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

void	render_tile(t_tile tile, t_rt *rt_dat)
{
	// clock_t	start;
	// clock_t	end;
	t_spp	spp;
	int		y;

	y = tile.start_y;
	spp.w = &rt_dat->world;
	spp.c = rt_dat->cam;
	spp.max_bounce_depth = rt_dat->max_bounce_depth;
	spp.spp = rt_dat->samples_per_pixel;
	spp.pss = 1.0 / rt_dat->samples_per_pixel;
	// start = clock();
	while (y < tile.end_y)
	{
		render_row(tile, spp, y, rt_dat);
		y++;
	}
	// end = clock();
	// printf("Chunk took %f seconds to execute \n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

void	queue_tiles(t_threadpool *tp)
{
	const int	tile_size = 64;
	int			px;
	int			py;

	tp->engine->render_start = monotonic_seconds();
	py = 0;
	while (py < tp->engine->img_h)
	{
		px = 0;
		while (px < tp->engine->img_w)
		{
			pthread_mutex_lock(&tp->queue_mutex);
			tp->queue[tp->tile_head].start_x = px;
			tp->queue[tp->tile_head].start_y = py;
			if ((tile_size + px) / tp->engine->img_w == 1)
				tp->queue[tp->tile_head].end_x = px + (tp->engine->img_w - px);
			else
				tp->queue[tp->tile_head].end_x = px + tile_size;
			if ((tile_size + py) / tp->engine->img_h == 1)
				tp->queue[tp->tile_head].end_y = py + (tp->engine->img_h - py);
			else
				tp->queue[tp->tile_head].end_y = py + tile_size;
			tp->tile_head = (tp->tile_head + 1) % tp->queue_size;
			tp->queue_cnt++;
			pthread_cond_signal(&tp->queue_cond);
			pthread_mutex_unlock(&tp->queue_mutex);
			px += tile_size;
		}
		py += tile_size;
	}
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
	ft_memset(win->mlx_dat->addr, 0, (size_t)win->mlx_dat->line_length * win->img_h);
	queue_tiles(win->tp);
}