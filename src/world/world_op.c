/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:07:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/21 12:10:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

#define NULL ((void *)0)

t_world	*world_add_back(t_world *world, t_objects *obj, t_obj_type type)
{
	t_objects	*p;

	if (!obj)
		return (NULL);
	if (!world || !world->objs)
	{
		world->objs = obj;
		world->objs->type = type;
		world->objs->next = NULL;
		return (world);
	}
	p = world->objs;
	while(p->next)
		p = p->next;
	p->next = obj;
	p->type = type;
	obj->next = NULL;
	return (world);
}
