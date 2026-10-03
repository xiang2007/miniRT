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

# include "objects.h"
# include <stdbool.h>

// Window Size
# define WIDTH 600
# define ASPECT_RATIO 1.0

// Control Panel Size
# define PANEL_W 300

// Translation
# define MOVE_X 0.3
# define MOVE_Y 0.3
# define EXPAND 0.3
# define SHIRNK 0.3

// Render Quality
# define HQ_BOUNCE_DEPTH 50
# define LQ_BOUNCE_DEPTH 1
# define HQ_SAMPLING 100
# define LQ_SAMPLING 1

// Camera
# define PI 3.14159265358979323846

// Light
# define LIGHT_WATTAGE 4300.0

// Material
# define DIELECTRIC_FUZZ 0.02
# define SHININESS 30
# define SPECULAR_STRENGTH 0.5

// Bump texture
# define STRENGTH 0.015

typedef struct s_threadpool	t_threadpool;
typedef struct s_cam		t_cam;
typedef struct s_world		t_world;
typedef struct s_objects	t_objects;
typedef struct s_rt			t_rt;

/**
 * @brief Mlx data
 * 
 *  - img2 and addr2 are there to ensure there's no screen tearing when
 * the img is being put onto the window while next one is being render.
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
}	t_mlx;

/**
 * @brief Ray tracer data
 * 
 * - test_file: contains the scene filename
 */
typedef struct s_rt
{
	int				img_h;
	int				img_w;

	int				max_bounce_depth;
	int				samples_per_pixel;

	t_mlx			*mlx_dat;
	t_cam			*cam;
	t_world			world;

	t_objects		*sel_obj;
	int				sel_light_id;
	int				sel_object_id;

	bool			is_rendering;
	bool			abort_flag;
	int				key;

	t_threadpool	*tp;

	double			render_start;
	double			render_time;
}	t_rt;

#endif
