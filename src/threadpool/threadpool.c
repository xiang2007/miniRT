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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static bool	claim_tile(t_threadpool *tp, t_tile *tile)
{
	pthread_mutex_lock(&tp->queue_mutex);
	while (tp->tile_next >= tp->tile_count && !tp->stop)
		pthread_cond_wait(&tp->queue_cond, &tp->queue_mutex);
	if (tp->stop)
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
		pthread_mutex_unlock(&tp->queue_mutex);
	}
	return (NULL);
}

t_threadpool	*threadpool_create(t_rt *engine, int thread_count)
{
	t_threadpool	*tp;
	int				i;

	if (thread_count == 0)
		thread_count = 2;
	tp = ft_calloc(1, sizeof(t_threadpool));
	if (!tp)
		return (NULL);
	tp->engine = engine;
	tp->thread_cnt = thread_count;
	tp->tile_capacity = ((engine->img_w + TILE_SIZE - 1) / TILE_SIZE)
		* ((engine->img_h + TILE_SIZE - 1) / TILE_SIZE);
	tp->tiles = malloc(sizeof(t_tile) * tp->tile_capacity);
	if (!tp->tiles)
		return (free(tp), NULL);
	tp->thread_id = malloc(sizeof(pthread_t) * thread_count);
	if (!tp->thread_id)
		return (free(tp->tiles), free(tp), NULL);
	pthread_mutex_init(&tp->queue_mutex, NULL);
	pthread_cond_init(&tp->queue_cond, NULL);
	i = -1;
	while (i++ < thread_count)
		pthread_create(&tp->thread_id[i], NULL, threadpool_worker, tp);
	return (tp);
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
