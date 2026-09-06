/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 00:33:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/23 17:02:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/objects.h"
#include <stdlib.h>

void	free_object_material(t_objects *o)
{
	if (o->type == OBJ_SPHERE)
		free(o->sphere.material);
	else if (o->type == OBJ_CYLINDER)
		free(o->cylinder.material);
	else if (o->type == OBJ_PLANE)
		free(o->plane.material);
	else if (o->type == OBJ_CONE)
		free(o->cone.material);
}

int	obj_bvh_count(t_objects *o)
{
	int			size;
	t_objects	*t;

	if (!o)
		return (-1);
	t = o;
	size = 0;
	while (t)
	{
		if (t->type == OBJ_SPHERE || t->type == OBJ_CYLINDER
			|| t->type == OBJ_CONE)
			size++;
		t = t->next;
	}
	return (size);
}
