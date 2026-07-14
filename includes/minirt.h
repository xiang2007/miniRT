/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:57:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/14 15:44:29 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1000
# define ASPECT_RATIO 1.7777777777777777777777777777778
# define MOVE_X 1
# define MOVE_Y 1
# define PI 3.14159265358979323846

#include "objects.h"

/**
 * @brief Mlx data
 */
typedef struct s_mlx
{
	void	*img;
	void	*addr;
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
	int			init;
	int			img_h;
	int			img_w;
	double		aspect_ratio;
	t_mlx		*mlx_dat;
	t_cam		*cam;
	t_world		world;
	t_objects	*sel_obj;
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

#endif