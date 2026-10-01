/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:43 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/14 17:19:24 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include <X11/keysym.h>
#include <math.h>

void	camera_move(int key, t_rt *rt)
{
	t_setup_cam	setup;
	t_vec3		move;

	move = create_vec3(0, 0, 0);
	if (key == XK_w)
		move = vec3_mul(rt->cam->w, -MOVE_Y);
	else if (key == XK_s)
		move = vec3_mul(rt->cam->w, MOVE_Y);
	else if (key == XK_a)
		move = vec3_mul(rt->cam->u, -MOVE_X);
	else if (key == XK_d)
		move = vec3_mul(rt->cam->u, MOVE_X);
	else if (key == XK_q)
		move = vec3_mul(rt->cam->v, -MOVE_Y);
	else if (key == XK_e)
		move = vec3_mul(rt->cam->v, MOVE_Y);
	setup.center = vec3_add(rt->cam->cam_center, move);
	setup.norm_vector = vec3_mul(rt->cam->w, -1.0);
	setup.fov = rt->cam->fov;
	cam_init(rt->cam, rt, &setup);
}

/**
 * @brief Setup camera viewport size, px delta, fov, and focal length.
 *
 * @param cam camera struct
 * @param m ray tracer data struct
 * @param s pre-camera setup struct
 */
void	cam_init(t_cam *cam, t_rt *m, t_setup_cam *s)
{
	cam->foc_len = 1.0;
	cam->cam_center = s->center;
	cam->vup = create_vec3(0, 1, 0);
	cam->lookfrom = s->center;
	cam->fov = s->fov;
	if (vec3_len(s->norm_vector) == 0.0)
		s->norm_vector = create_vec3(0, 0, -1);
	cam->w = unit_vec3(vec3_mul(s->norm_vector, -1.0));
	cam->lookat = vec3_add(cam->lookfrom, s->norm_vector);
	if (fabs(vec3_dot(cam->vup, cam->w)) > 0.999)
		cam->vup = create_vec3(0, 0, 1);
	cam->u = unit_vec3(vec3_cross(cam->w, cam->vup));
	cam->v = vec3_cross(cam->u, cam->w);
	cam->h = tan((cam->fov * PI / 180.0) / 2.0);
	cam->vp_h = 2.0 * cam->h * cam->foc_len;
	cam->vp_w = cam->vp_h * ((double)m->img_w / m->img_h);
	cam->vp_u = vec3_mul(cam->u, cam->vp_w);
	cam->vp_v = vec3_mul(cam->v, -cam->vp_h);
	cam->px_delta_u = vec3_div(cam->vp_u, m->img_w);
	cam->px_delta_v = vec3_div(cam->vp_v, m->img_h);
	cam->vp_upper_left = vec3_sub(vec3_sub(vec3_sub(cam->cam_center,
					vec3_mul(cam->w, cam->foc_len)), vec3_div(cam->vp_u, 2.0)),
			vec3_div(cam->vp_v, 2.0));
	cam->px00_loc = vec3_add(cam->vp_upper_left,
			vec3_mul(vec3_add(cam->px_delta_u, cam->px_delta_v), 0.5));
}

void	get_setup_cam(t_setup_cam *s, t_objects *objs)
{
	while (objs)
	{
		if (objs->type == OBJ_SETUP_CAM)
		{
			s->center = objs->cam_setup.center;
			s->norm_vector = objs->cam_setup.norm_vector;
			s->fov = objs->cam_setup.fov;
			return ;
		}
		objs = objs->next;
	}
}

void	camera_rotate(int key, t_rt *win)
{
	t_setup_cam	setup;
	t_vec3		rot_axis;
	double		angle;
	t_vec3		cur_look_dir;
	t_vec3		new_dir;

	if (key == XK_Left || key == XK_Up)
		angle = -0.1;
	else if (key == XK_Right || key == XK_Down)
		angle = 0.1;
	else
		return ;
	cur_look_dir = vec3_mul(win->cam->w, -1.0);
	if (key == XK_Left || key == XK_Right)
		rot_axis = create_vec3(0, 1, 0);
	else
		rot_axis = win->cam->u;
	new_dir = unit_vec3(vec3_rotate(cur_look_dir, rot_axis, angle));
	if ((key == XK_Up || key == XK_Down) && fabs(new_dir.y) > 0.999)
		return ;
	setup.center = win->cam->cam_center;
	setup.norm_vector = new_dir;
	setup.fov = win->cam->fov;
	cam_init(win->cam, win, &setup);
}
