/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 13:05:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 00:48:36 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"

static void	start_threads(t_threadpool *tp, int thread_count)
{
	int	i;

	pthread_mutex_init(&tp->queue_mutex, NULL);
	pthread_cond_init(&tp->queue_cond, NULL);
	pthread_cond_init(&tp->done_cond, NULL);
	i = 0;
	while (i < thread_count)
	{
		pthread_create(&tp->thread_id[i], NULL, threadpool_worker, tp);
		i++;
	}
}

t_threadpool	*threadpool_create(t_rt *engine, int thread_count)
{
	t_threadpool	*tp;

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
	start_threads(tp, thread_count);
	return (tp);
}
