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

#include "../../includes/minirt.h"
#include "../../includes/vec3.h"
#include "../../includes/camera.h"
#include <X11/keysym.h>
#include <math.h>

void	camera_move(int key, t_rt *rt)
{
	t_setup_cam	setup;
	t_vec3		move;

	move = create_vec3(0, 0, 0);
	if (key == XK_w)
		move = vec_mul(rt->cam->w, -MOVE_Y);
	else if (key == XK_s)
		move = vec_mul(rt->cam->w, MOVE_Y);
	else if (key == XK_a)
		move = vec_mul(rt->cam->u, -MOVE_X);
	else if (key == XK_d)
		move = vec_mul(rt->cam->u, MOVE_X);
	else if (key == XK_q)
		move = vec_mul(rt->cam->v, -MOVE_Y);
	else if (key == XK_e)
		move = vec_mul(rt->cam->v, MOVE_Y);
	setup.center = vec_add(rt->cam->cam_center, move);
	setup.norm_vector = vec_mul(rt->cam->w, -1.0);
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
	if (vec_len(s->norm_vector) == 0.0)
		s->norm_vector = create_vec3(0, 0, -1);
	cam->w = unit_vec(vec_mul(s->norm_vector, -1.0));
	cam->lookat = vec_add(cam->lookfrom, s->norm_vector);
	if (fabs(vec_dot(cam->vup, cam->w)) > 0.999)
		cam->vup = create_vec3(0, 0, 1);
	cam->u = unit_vec(vec_cross(cam->vup, cam->w));
	cam->v = vec_cross(cam->w, cam->u);
	cam->h = tan((cam->fov * PI / 180.0) / 2.0);
	cam->vp_h = 2.0 * cam->h * cam->foc_len;
	cam->vp_w = cam->vp_h * ((double)m->img_w / m->img_h);
	cam->vp_u = vec_mul(cam->u, cam->vp_w);
	cam->vp_v = vec_mul((vec_mul(cam->v, -1)), cam->vp_h);
	cam->px_delta_u = vec_div(cam->vp_u, m->img_w);
	cam->px_delta_v = vec_div(cam->vp_v, m->img_h);
	cam->vp_upper_left = vec_sub(vec_sub(vec_sub(cam->cam_center,
					vec_mul(cam->w, cam->foc_len)), vec_div(cam->vp_u, 2.0)),
			vec_div(cam->vp_v, 2.0));
	cam->px00_loc = vec_add(cam->vp_upper_left, vec_mul(vec_add(cam->px_delta_u,
					cam->px_delta_v), 0.5));
}
