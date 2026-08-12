/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:19:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 15:22:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "ray.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/render.h"
#include "../../includes/aabb.h"
#include "../../includes/camera.h"
#include "objects.h"
#include <X11/keysym.h>
#include "material.h"
#include "parse.h"

void	handle_key_z(t_rt *win)
{
	reset_res(win);
	render(win, win->cam, &win->world);
}

void	handle_camera_move(int key, t_rt *win)
{
	camera_move(key, win);
	lower_res(key, win);
	render(win, win->cam, &win->world);
}

void	handle_move_object(int key, t_rt *win)
{
	move_objects(key, &win->sel_obj);
	if (win->sel_obj->type == OBJ_SPHERE || win->sel_obj->type == OBJ_CYLINDER)
		rebuild_world_bvh(&win->world);
	lower_res(key, win);
	render(win, win->cam, &win->world);
}

static void	rotate_axis_key(int key, t_vec3 *axis, double *angle)
{
	*axis = create_vec3(0, 0, 0);
	*angle = 0;
	if (key == XK_bracketleft)
		*axis = create_vec3(0, 1, 0), *angle = -0.1;
	else if (key == XK_bracketright)
		*axis = create_vec3(0, 1, 0), *angle = 0.1;
	else if (key == XK_semicolon)
		*axis = create_vec3(1, 0, 0), *angle = -0.1;
	else if (key == XK_apostrophe)
		*axis = create_vec3(1, 0, 0), *angle = 0.1;
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
	else
		return ;	/* sphere: no rotation; light: no rotation */
	lower_res(key, win);
	if (o->type == OBJ_CYLINDER)
		rebuild_world_bvh(&win->world);	/* AABB changes with the axis */
	render(win, win->cam, &win->world);
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
	render(win, win->cam, &win->world);
}

static t_ray	click_ray(t_rt *win, int x, int y)
{
	t_vec3	px_sample;
	t_vec3	dir;

	px_sample = vec_add(win->cam->px00_loc,
			vec_add(vec_mul(win->cam->px_delta_u, (double)x),
				vec_mul(win->cam->px_delta_v, (double)y)));
	dir = vec_sub(px_sample, win->cam->cam_center);
	return (ray(win->cam->cam_center, dir));
}

int	mouse_select(int button, int x, int y, t_rt *win)
{
	t_ray		r;
	t_hit_dat	rec;

	if (button != 1 || !win->cam)
		return (0);
	r = click_ray(win, x, y);
	rec = (t_hit_dat){0};
	if (hit_list(&r, &win->world, &rec) && rec.hit_obj)
	{
		win->sel_obj = rec.hit_obj;
		printf("Clicked object selected: ");
		print_object(rec.hit_obj);
	}
	return (0);
}
