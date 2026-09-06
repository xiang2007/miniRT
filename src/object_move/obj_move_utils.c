/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 20:06:11 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/29 18:38:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"
#include "../../includes/minirt.h"
#include <X11/keysym.h>

void	light_translate(t_objects *self, int key)
{
	if (key == XK_Up)
		self->light.cords.y += MOVE_Y;
	else if (key == XK_Down)
		self->light.cords.y -= MOVE_Y;
	else if (key == XK_Left)
		self->light.cords.x += MOVE_X;
	else if (key == XK_Right)
		self->light.cords.x -= MOVE_X;
}
