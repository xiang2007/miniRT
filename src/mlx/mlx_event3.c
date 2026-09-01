/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:19:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:14:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include "../../includes/minirt.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/camera.h"
#include "vec3.h"
#include <X11/keysym.h>

void	handle_key_z(t_rt *win)
{
	reset_res(win);
	queue_render(win);
}

void	handle_camera_move(int key, t_rt *win)
{
	camera_move(key, win);
	lower_res(key, win);
	queue_render(win);
}

void	handle_move_object(int key, t_rt *win)
{
	if (!win->sel_obj)
		return ;
	move_objects(key, &win->sel_obj);
	if (win->sel_obj->type == OBJ_SPHERE || win->sel_obj->type == OBJ_CYLINDER || win->sel_obj->type == OBJ_CONE)
		rebuild_world_bvh(&win->world);
	lower_res(key, win);
	queue_render(win);
}

void	handle_rotate_object(int key, t_rt *win)
{
	t_objects	*o;
	t_vec3		axis;
	double		angle;

	rotate_axis_key(key, &axis, &angle);
	o = win->sel_obj;
	if (o->type == OBJ_CYLINDER)
		o->cylinder.axis = unit_vec(vec_rotate(o->cylinder.axis, axis, angle));
	else if (o->type == OBJ_PLANE)
		o->plane.normal = unit_vec(vec_rotate(o->plane.normal, axis, angle));
	else if (o->type == OBJ_CONE)
		o->cone.axis = unit_vec(vec_rotate(o->cone.axis, axis, angle));
	else
		return ;
	lower_res(key, win);
	if (o->type == OBJ_CYLINDER || o->type == OBJ_CONE)
		rebuild_world_bvh(&win->world);
	queue_render(win);
}

void	handle_camera_rotate(int key, t_rt *win)
{
	t_setup_cam	setup;
	t_vec3		axis;
	double		angle;

	rotate_axis_key(key, &axis, &angle);
	setup.center = win->cam->cam_center;
	setup.norm_vector = unit_vec(
			vec_rotate(vec_mul(win->cam->w, -1.0), axis, angle));
	setup.fov = win->cam->fov;
	cam_init(win->cam, win, &setup);
	lower_res(key, win);
	queue_render(win);
}
