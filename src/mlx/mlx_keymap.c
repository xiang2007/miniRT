/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 08:50:55 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_dat.h"
#include "camera.h"
#include <X11/keysym.h>

static void	move_selection(int key, t_rt *dat)
{
	if (dat->sel_obj)
	{
		dat->sel_obj->translate(dat->sel_obj, key);
		if (dat->sel_obj->type == OBJ_SPHERE
			|| dat->sel_obj->type == OBJ_CYLINDER
			|| dat->sel_obj->type == OBJ_CONE)
			rebuild_world_bvh(&dat->world);
	}
	else
		camera_move(key, dat);
}

void	keymap(int key, t_rt *dat)
{
	if (key >= XK_Left && key <= XK_Down)
	{
		if (dat->sel_obj)
			handle_rotate_object(key, dat);
		else
			handle_camera_rotate(key, dat);
	}
	else if (key == XK_w || key == XK_s || key == XK_a || key == XK_d
		|| key == XK_q || key == XK_e || key == XK_equal || key == XK_minus)
	{
		move_selection(key, dat);
	}
	else if (key == XK_c)
		toggle_checker(dat->sel_obj);
	else if (key == XK_r)
		handle_light(dat);
	else if (key == XK_v)
		handle_sel_object(dat);
	if (key == XK_z)
	{
		dat->max_bounce_depth = 50;
		dat->samples_per_pixel = 100;
	}
	else
		reset_res(dat);
}
