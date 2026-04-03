/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:43 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/19 17:51:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include "camera.h"

void	cam_init(t_cam *cam, t_rt *m)
{
	cam->foc_len = 1.0;
	cam->vp_h = 2.0;
	cam->vp_w = cam->vp_h * ((double)m->img_w / m->img_h);
	cam->cam_center = create_vec3(0.0, 0.0, 0.0);
	cam->vp_u = create_vec3(cam->vp_w, 0.0, 0.0);
	cam->vp_v = create_vec3(0.0, -(cam->vp_h), 0.0);
	cam->px_delta_u = vec_div(cam->vp_u, m->img_w);
	cam->px_delta_v = vec_div(cam->vp_v, m->img_h);
	cam->vp_upper_left = vec_sub(vec_sub(vec_sub(cam->cam_center,
					create_vec3(0.0, 0.0, 1.0)), vec_div(cam->vp_u, 2.0)),
			vec_div(cam->vp_v, 2.0));
	cam->px00_loc = vec_add(cam->vp_upper_left, vec_mul(vec_add(cam->px_delta_u,
					cam->px_delta_v), 0.5));
}
