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
#include <math.h>

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

static void	fill_tile(t_threadpool *tp, t_rt *rt, int px, int py, int i)
{
	tp->tiles[i].start_x = px;
	tp->tiles[i].start_y = py;
	tp->tiles[i].end_x = fmin(px + TILE_SIZE, rt->img_w);
	tp->tiles[i].end_y = fmin(py + TILE_SIZE, rt->img_h);
}

void	queue_tiles(t_threadpool *tp)
{
	t_rt	*rt;
	int		px;
	int		py;
	int		i;

	rt = tp->engine;
	rt->render_start = monotonic_seconds();
	i = 0;
	py = 0;
	while (py < rt->img_h)
	{
		px = 0;
		while (px < rt->img_w)
		{
			fill_tile(tp, rt, px, py, i);
			i++;
			px += TILE_SIZE;
		}
		py += TILE_SIZE;
	}
	pthread_mutex_lock(&tp->queue_mutex);
	tp->tile_count = i;
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
	ft_memset(win->mlx_dat->addr, 0, (size_t)win->mlx_dat->line_length * win->img_h);
	queue_tiles(win->tp);
}