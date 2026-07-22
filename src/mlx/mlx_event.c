/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:39:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 20:15:37 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../mlx_Linux/mlx.h"
#include "../../includes/parse.h"
#include "../../includes/mlx_dat.h"
#include "../../includes/render.h"
#include "../../includes/aabb.h"
#include "../../includes/camera.h"
#include <X11/keysym.h>
#include <stdlib.h>

static void	rebuild_world_bvh(t_world *world)
{
	t_objects	**objects;
	t_bvh		*root;
	int			count;

	count = obj_sphere_count(world->objs);
	objects = Obj2Arr(world->objs);
	if (!objects || count <= 0)
		return (free(objects));
	root = build_bvh(objects, 0, count);
	if (!root)
		return (free(objects));
	free_bvh(world->bvh);
	free(world->bvh_obj);
	world->bvh = root;
	world->bvh_obj = objects;
}

/**
 * @brief Frees all obj structs in world
 *
 * @param world world struct
 */
void	world_free(t_world *world)
{
	t_objects	*tmp;

	if (!world)
		return ;
	free_bvh(world->bvh);
	free(world->bvh_obj);
	world->bvh = NULL;
	world->bvh_obj = NULL;
	while (world->objs)
	{
		tmp = world->objs;
		world->objs = world->objs->next;
		if (tmp->type == OBJ_SPHERE)
			free(tmp->sphere.material);
		free(tmp);
	}
}

/**
 * @brief Checks if a key pressed
 * - If Escape Key is pressed, all malloced data are freed and exit with 0
 *
 * @param key key pressed
 * @param win window data
 * @return returns 0
 */
int	handle_key(int key, t_rt *win)
{
	if (key == XK_Escape)
	{
		world_free(&win->world);
		mlx_dat_free(win->mlx_dat);
		free(win->cam);
		exit(0);
	}
	if (key == XK_r)
		reload_scene(win);
	if (key >= XK_0 && key <= XK_9)
		win->sel_obj = select_object(key, &win->world);
	if (key >= XK_Left && key <= XK_Down && win->sel_obj)
	{
		move_objects(key, &win->sel_obj);
		if (win->sel_obj->type == OBJ_SPHERE)
			rebuild_world_bvh(&win->world);
		lower_res(key, win);
		render(win, win->cam, &win->world);
	}
	if (key == XK_w || key == XK_s || key == XK_a
		|| key == XK_d || key == XK_q || key == XK_e)
	{
		camera_move(key, win);
		lower_res(key, win);
		render(win, win->cam, &win->world);
	}
	if (key == XK_z)
	{
		reset_res(win);
		render(win, win->cam, &win->world);
	}
	return (0);
}

/**
 * @brief Frees all malloced data
 *
 * @param win window data
 * @return returns nothingv
 */
int	close_all(t_rt *win)
{
	world_free(&win->world);
	mlx_dat_free(win->mlx_dat);
	exit(0);
}
