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
#include "../../mlx_Linux/mlx.h"
#include "../../includes/parse.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/render.h"
#include "../../includes/aabb.h"
#include "../../includes/camera.h"
#include "objects.h"
#include <X11/keysym.h>
#include <stdlib.h>

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
