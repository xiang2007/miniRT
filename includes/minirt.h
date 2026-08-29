/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:57:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:27:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "threadpool.h"
# include <stdbool.h>
# include <math.h>
# include <float.h>
# include <stddef.h>
# define WIDTH 600
# define ASPECT_RATIO 1.0
# define PANEL_W 300
# define MOVE_X 0.3
# define MOVE_Y 0.3
# define EXPAND 0.3
# define SHIRNK 0.3
# define MAX_BOUNCE 50
# define LOW_RES_BOUNCE 10
# define LOW_RES_SPP 3
# define SPP 100
# define PI 3.14159265358979323846

# define LIGHT_WATTAGE 4300.0
# define DIELECTRIC_FUZZ 0.02

# include "objects.h"

typedef struct s_threadpool	t_threadpool;
typedef struct s_cam		t_cam;
typedef struct s_world		t_world;
typedef struct s_objects	t_objects;

/**
 * @brief Mlx data
 */
typedef struct s_mlx
{
	void	*img;
	void	*addr;
	void	*img2;
	void	*addr2;
	void	*mlx;
	void	*mlx_win;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx;

/**
 * @brief Ray tracer data
 *
 * - img_h: image height
 * - img_w: image width
 * - vp_h: viewport height
 * - vp_w: viewport width
 * - mlx_dat: mlx data
 * - aspect_ratio: aspect ratio number
 */
typedef struct s_rt
{
	int				init;
	int				img_h;
	int				img_w;
	int				max_bounce_depth;
	int				old_max_bounce_depth;
	int				samples_per_pixel;
	int				old_sampels_per_pixel;
	int				show_controls;
	double			pixel_samples_scale;
	double			old_pixel_samples_scale;
	double			aspect_ratio;
	t_mlx			*mlx_dat;
	t_cam			*cam;
	t_world			world;
	t_objects		*sel_obj;
	char			*test_file;
	bool			is_rendering;
	t_threadpool	*tp;
	int				pending_key;
	bool			has_pending;
	double			render_start;
	double			render_time;
}				t_rt;

// typedef struct s_interval
// {
// 	double	min;
// 	double	max;
// }				t_interval;
//
// typedef struct s_ray_min_max
// {
// 	double	r_min;
// 	double	r_max;
// }				t_ray_min_max;

int		reload_scene(t_rt *win);
void	rt_dat_init(t_rt *rt_dat);
void	rt_dat_free(t_rt *rt_dat);
void	setup_cam_init(t_setup_cam *s);

#endif
