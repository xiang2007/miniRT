/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:27:46 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/14 15:20:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "objects.h"

void	cam_init(t_cam *cam, t_rt *m, t_setup_cam *s);
void	camera_move(int key, t_rt *rt);

#endif
