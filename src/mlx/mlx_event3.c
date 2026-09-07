/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:19:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/07 09:37:10 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "../../includes/minirt.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/camera.h"
#include "vec3.h"
#include <X11/keysym.h>
#include <pthread.h>

void	handle_key_z(t_rt *win)
{
	reset_res(win);
	win->needs_rerender = true;
}

void	handle_camera_move(int key, t_rt *win)
{
	camera_move(key, win);
	lower_res(key, win);
	win->needs_rerender = true;
}

void	handle_move_object(int key, t_rt *win)
{
	if (!win->sel_obj)
		return ;
	if (win->sel_obj->translate)
	{
		win->sel_obj->translate(win->sel_obj, key);
	}
	if (win->sel_obj->type == OBJ_SPHERE
			|| win->sel_obj->type == OBJ_CYLINDER
				|| win->sel_obj->type == OBJ_CONE)
		win->bvh_dirty = true;
	lower_res(key, win);
	win->needs_rerender = true;
}

void	handle_rotate_object(int key, t_rt *win)
{
	t_objects	*o;

	o = win->sel_obj;
	if (o->type == OBJ_CYLINDER || o->type == OBJ_PLANE
			|| o->type == OBJ_CONE)
		o->rotate(o, key);
	else
		return ;
	if (o->type == OBJ_CYLINDER || o->type == OBJ_CONE)
		win->bvh_dirty = true;
	lower_res(key, win);
	win->needs_rerender = true;
}

void	handle_camera_rotate(int key, t_rt *win)
{
	t_setup_cam	setup;
	t_vec3		axis;
	double		angle;

	rotate_axis_key(key, &axis, &angle);
	setup.center = win->cam->cam_center;
	setup.norm_vector = unit_vec3(
			vec3_rotate(vec3_mul(win->cam->w, -1.0),
				axis, angle));
	setup.fov = win->cam->fov;
	cam_init(win->cam, win, &setup);
	lower_res(key, win);
	win->needs_rerender = true;
}
