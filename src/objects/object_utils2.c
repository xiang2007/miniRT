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

#include "../../includes/parse.h"

int	obj_size(t_objects *o)
{
	t_objects	*t;
	int			size;

	size = 0;
	if (!o)
		return (-1);
	t = o;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
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
		if (t->type == OBJ_SPHERE || t->type == OBJ_CYLINDER)
			size++;
		t = t->next;
	}
	return (size);
}
