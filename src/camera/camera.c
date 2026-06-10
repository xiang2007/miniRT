/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:43 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/16 11:57:23 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include "camera.h"

/**
 * @brief Setup camera viewport size, px delta, fov, and focal length.
 *
 * @param cam camera struct
 * @param m ray tracer data struct
 * @param s pre-camera setup struct
 */
void	cam_init(t_cam *cam, t_rt *m, t_setup_cam *s)
{
	cam->fov = s->fov;
	cam->foc_len = 1.0;
	cam->vp_h = 2.0;
	cam->vp_w = cam->vp_h * ((double)m->img_w / m->img_h);
	cam->cam_center = s->center;
	cam->vp_u = create_vec3(cam->vp_w, s->norm_vector.y, s->norm_vector.z);
	cam->vp_v = create_vec3(s->norm_vector.x, -(cam->vp_h), s->norm_vector.z);
	cam->px_delta_u = vec_div(cam->vp_u, m->img_w);
	cam->px_delta_v = vec_div(cam->vp_v, m->img_h);
	cam->vp_upper_left = vec_sub(vec_sub(vec_sub(cam->cam_center,
					create_vec3(0.0, 0.0, 1.0)), vec_div(cam->vp_u, 2.0)),
			vec_div(cam->vp_v, 2.0));
	cam->px00_loc = vec_add(cam->vp_upper_left, vec_mul(vec_add(cam->px_delta_u,
					cam->px_delta_v), 0.5));
}
