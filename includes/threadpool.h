/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:02:45 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/14 19:02:45 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADPOOL_H
# define THREADPOOL_H

#include "minirt.h"
#include <pthread.h>

# define TILE_SIZE 64

typedef struct s_tile
{
    int		start_x;
    int		start_y;
    int		end_x;
    int		end_y;
}	t_tile;

typedef struct s_threadpool
{
	int				tile_next;
	int				tile_count;
	int				tile_capacity;
	t_tile			*tiles;
	pthread_mutex_t	queue_mutex;
	pthread_cond_t	queue_cond;
	size_t			thread_cnt;
	int				active_threads;
	bool			stop;
	pthread_t		*thread_id;
	t_rt			*engine;
}	t_threadpool;

t_threadpool	*threadpool_create(t_rt *engine, int thread_count);
void			*threadpool_worker(void *arg);
void			queue_tiles(t_threadpool *tp);
void			render_tile(t_tile tile, t_rt *rt_dat);
void			queue_render(t_rt *win);
void			threadpool_destroy(t_threadpool *tp);
double			monotonic_seconds(void);

#endif