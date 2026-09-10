/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 13:05:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 00:48:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "libft.h"
#include "minirt.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static bool	claim_tile(t_threadpool *tp, t_tile *tile)
{
	pthread_mutex_lock(&tp->queue_mutex);
	while (tp->tile_next >= tp->tile_count && !tp->stop)
		pthread_cond_wait(&tp->queue_cond, &tp->queue_mutex);
	if (tp->engine->abort_flag)
	{
		pthread_mutex_unlock(&tp->queue_mutex);
		return (false);
	}
	*tile = tp->tiles[tp->tile_next];
	tp->tile_next++;
	tp->active_threads++;
	pthread_mutex_unlock(&tp->queue_mutex);
	return (true);
}

void	*threadpool_worker(void *arg)
{
	t_threadpool	*tp;
	t_tile			tile;

	tp = (t_threadpool *)arg;
	while (claim_tile(tp, &tile))
	{
		render_tile(tile, tp->engine);
		pthread_mutex_lock(&tp->queue_mutex);
		tp->active_threads--;
		if (tp->active_threads == 0)
			pthread_cond_broadcast(&tp->done_cond);
		pthread_mutex_unlock(&tp->queue_mutex);
	}
	return (NULL);
}

void	threadpool_destroy(t_threadpool *tp)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&tp->queue_mutex);
	tp->stop = true;
	pthread_mutex_unlock(&tp->queue_mutex);
	pthread_cond_broadcast(&tp->queue_cond);
	while (i < tp->thread_cnt)
	{
		pthread_join(tp->thread_id[i], NULL);
		i++;
	}
	free(tp->tiles);
	free(tp->thread_id);
	free(tp);
}

bool	threads_idle_locked(t_threadpool *tp)
{
	if (tp->active_threads == 0)
		return (true);
	return (false);
}
