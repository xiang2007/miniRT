/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:27:46 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/03 12:27:46 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_cam
{
	double	foc_len;
	double	vp_h;
	double	vp_w;
	t_vec3	cam_center;
	t_vec3	vp_u;
	t_vec3	vp_v;
	t_vec3	px_delta_u;
	t_vec3	px_delta_v;
	t_vec3	vp_upper_left;
	t_vec3	px00_loc;
}				t_cam;

void	cam_init(t_cam *cam, t_rt *m);

#endif
