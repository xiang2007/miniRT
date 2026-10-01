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

static void	handle_rotate_object(int key, t_rt *win)
{
	t_objects	*o;

	o = win->sel_obj;
	if (o->type == OBJ_CYLINDER || o->type == OBJ_PLANE
		|| o->type == OBJ_CONE)
		o->rotate(o, key);
	else
		return ;
	if (o->type == OBJ_CYLINDER || o->type == OBJ_CONE)
		rebuild_world_bvh(&win->world);
}

static void	reset_sampling(t_rt *rt)
{
	rt->max_bounce_depth = LQ_BOUNCE_DEPTH;
	rt->samples_per_pixel = LQ_SAMPLING;
}

void	keymap(int key, t_rt *dat)
{
	if (key >= XK_Left && key <= XK_Down)
	{
		if (dat->sel_obj)
			handle_rotate_object(key, dat);
		else
			camera_rotate(key, dat);
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
		dat->max_bounce_depth = HQ_BOUNCE_DEPTH;
		dat->samples_per_pixel = HQ_SAMPLING;
	}
	else
		reset_sampling(dat);
}
