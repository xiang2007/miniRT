/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:07:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/13 18:09:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stddef.h>

void	world_add_back(t_world *world, t_objects *obj, t_obj_type type)
{
	t_objects	*p;

	if (!obj)
		return ;
	if (!world || !world->objs)
	{
		world->objs = obj;
		world->objs->type = type;
		world->objs->next = NULL;
		return ;
	}
	p = world->objs;
	while (p->next)
		p = p->next;
	p->next = obj;
	obj->type = type;
	obj->next = NULL;
}
