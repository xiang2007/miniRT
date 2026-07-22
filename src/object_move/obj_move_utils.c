/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 20:06:11 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/13 14:43:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"
#include "../../includes/minirt.h"
#include <X11/keysym.h>

void *cylinder_mv(int key, t_objects *o)
{
	if (key == XK_Up)
		return (o->cylinder.center.y += MOVE_Y, ((void *)0));
	else if (key == XK_Down)
		return (o->cylinder.center.y -= MOVE_Y, ((void *)0));
	else if (key == XK_Left)
		return (o->cylinder.center.x -= MOVE_X, ((void *)0));
	else if (key == XK_Right)
		return (o->cylinder.center.x += MOVE_X, ((void *)0));
	return ((void *)0);
}

void *sphere_mv(int key, t_objects *o)
{
	if (key == XK_Up)
		return (o->sphere.point.y += MOVE_Y, ((void *)0));
	else if (key == XK_Down)
		return (o->sphere.point.y -= MOVE_Y, ((void *)0));
	else if (key == XK_Left)
		return (o->sphere.point.x -= MOVE_X, ((void *)0));
	else if (key == XK_Right)
		return (o->sphere.point.x += MOVE_X, ((void *)0));
	return ((void *)0);
}

void *plane_mv(int key, t_objects *o)
{
	if (key == XK_Up)
		return (o->plane.center.y += MOVE_Y, ((void *)0));
	else if (key == XK_Down)
		return (o->plane.center.y -= MOVE_Y, ((void *)0));
	else if (key == XK_Left)
		return (o->plane.center.x -= MOVE_X, ((void *)0));
	else if (key == XK_Right)
		return (o->plane.center.x += MOVE_X, ((void *)0));
	return ((void *)0);
}

void	*light_mv(int key, t_objects *o)
{
	if (key == XK_Up)
		o->light.cords.y += MOVE_Y;
	else if (key == XK_Down)
		o->light.cords.y -= MOVE_Y;
	else if (key == XK_Left)
		o->light.cords.x -= MOVE_X;
	else if (key == XK_Right)
		o->light.cords.x += MOVE_X;
	return ((void *)0);
}
