/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 13:05:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/15 13:05:54 by ydylan-k         ###   ########.fr       */
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
void	*threadpool_worker(void *arg)
{
	t_threadpool	*tp = arg;
	t_tile			tile;

	while (1)
	{
		pthread_mutex_lock(&(tp->queue_mutex));
		while (tp->queue_cnt == 0 && !tp->stop)
			pthread_cond_wait(&(tp->queue_cond), &(tp->queue_mutex));
		if (tp->stop)
			break ;
		tile = tp->queue[tp->tile_tail];
		tp->tile_tail = (tp->tile_tail + 1) % tp->queue_size;
		tp->queue_cnt--;
		tp->active_threads++;
		pthread_mutex_unlock(&(tp->queue_mutex));
		render_tile(tile, tp->engine);
		pthread_mutex_lock(&(tp->queue_mutex));
		tp->active_threads--;
		pthread_mutex_unlock(&(tp->queue_mutex));
	}
	pthread_cond_signal(&(tp->queue_cond));
	pthread_mutex_unlock(&(tp->queue_mutex));
	return (NULL);
}

t_threadpool	*threadpool_create(t_rt *engine, int thread_count, int queue_size)
{
	t_threadpool	*tp;
	int				i;

	if (thread_count == 0)
		thread_count = 2;
	tp = ft_calloc(1, sizeof(t_threadpool));
	tp->thread_cnt = thread_count;
	tp->tile_head = 0;
	tp->tile_tail = 0;
	tp->queue_cnt = 0;
	tp->active_threads = 0;
	tp->stop = false;
	tp->engine = engine;
	tp->queue_size = queue_size;
	tp->queue = malloc(sizeof(t_tile) * queue_size);
	pthread_mutex_init(&tp->queue_mutex, NULL);
	pthread_cond_init(&tp->queue_cond, NULL);
	i = 0;
	tp->thread_id = malloc(sizeof(pthread_t) * thread_count);
	while (i < thread_count)
	{
		pthread_create(&tp->thread_id[i], NULL, threadpool_worker, (void *)tp);
		i++;
	}
	return (tp);
}

void	threadpool_destroy(t_threadpool *tp)
{
	size_t	i;

	i  = 0;
	pthread_mutex_lock(&tp->queue_mutex);
	tp->stop = true;
	pthread_mutex_unlock(&tp->queue_mutex);
	pthread_cond_broadcast(&tp->queue_cond);
	while (i < tp->thread_cnt)
	{
		pthread_join(tp->thread_id[i], NULL);
		i++;
	}
	free(tp->queue);
	free(tp->thread_id);
	free(tp);
}